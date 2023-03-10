/* eslint-disable prettier/prettier */
import { Inject, Injectable, forwardRef } from '@nestjs/common';
import { ActiveGameDto, FriendDto, FriendRequestDto, MatchDto, StatisticsDto, PrivateProfileDto, PublicProfileDto, Game, Relation, BlockDto } from '../dtos/profile.dtos';
import { AuthService } from 'src/auth/auth.service';
import { prisma } from 'src/main';
import { responseDefault, responseUploadPhoto } from "src/dtos/responseTools.dtos";
import { User, userStatus } from '@prisma/client';

@Injectable()
export class ProfileService {
    @Inject(forwardRef(() => AuthService))
    private readonly authService: AuthService

    async authentificate(data: Request): Promise<string> {
        return (await this.authService.authentificateSession(data));
    }

    insertFriend(user: string, photo: string, status: string, friendlist: any) {
        const newFriend = new FriendDto(user, photo, status);
        friendlist.push(newFriend);
    }

    insertFriendRequest(from: string, photo: string, friendlist: any) {
        const newFriendRequest = new FriendRequestDto(from, photo);
        friendlist.push(newFriendRequest);
    }

    insertMatch(leftPlayer: string, leftPhoto: string, leftScore: number,
        rightPlayer: string, rightPhoto: string, rightScore: number,
        winner: string, updated: Date, matchHistory: any) {
        const newMatch = new MatchDto(leftPlayer, leftPhoto, leftScore, rightPlayer,
            rightPhoto, rightScore, winner, updated);
        matchHistory.push(newMatch);
    }

    async getUserRelation(client: string, otherUser: string): Promise<Relation>
    {
        let user0;
        let user1;

        if (client == undefined || otherUser == undefined)
            return new Relation(true, false, false);
        try {
            user0 = await prisma.user.findUnique({
                where: {
                    login42: client,
                },
            });

            user1 = await prisma.user.findUnique({
                where: {
                    username: otherUser,
                },
            });
        }
        catch {}

        if (!user0 || !user1) {
            return new Relation(true, false, false);
        }
        //  Look if they are friend or blocked
        var friend = false;
        var block = false;
        try
        {
            var request = await prisma.friendRequest.findUnique({
                where: {
                    sender_receiver:
                    {
                        sender: client,
                        receiver: user1.login42
                    }
                }
            })

            if (request)
                friend = true;

            request = await prisma.friendRequest.findUnique({
                where: {
                    sender_receiver:
                    {
                        sender: user1.login42,
                        receiver: client
                    }
                    }
                })

            if (request)
                friend = true;

            var blockReq = await prisma.block.findUnique({
                where: {
                    blocker_blocked :
                    {
                        blocker: client,
                        blocked: user1.login42
                    }
                }
            })

            if (blockReq)
                block = true;
        }
        catch (error)
        {
            return new Relation(true, false, false);
        }

        return new Relation(false, friend, block);
    }

    async getProfilePublic(asker: string, login42: string): Promise<PublicProfileDto>
    {
        // Create prisma client and look if the username exist in the database

        let user;

        try {
            user = await prisma.user.findUnique({
                where: {
                    username: login42,
                },
            });
        }
        catch { }

        //  If he dosen't exist, return error true and everything at null
        if (!user) {
            return new PublicProfileDto(true, null, null, null, null, null, null, null);
        }

        var goingto = login42;

        try
        {
            let temp = await prisma.user.findUnique({
                where: {
                    login42: asker
                }
            })
            goingto = temp.username;
        }
        catch{}

        let friendList: FriendDto[] = [];
        let friendRequests: FriendRequestDto[] = [];
        let matchHistory: MatchDto[] = [];
    
        //  Build the response

        //  Get friends of user
        const friendSent = await prisma.friendRequest.findMany({
            where: {
                sender: user.login42,
                status: 'accepted',
            }
        })

        const friendReceived = await prisma.friendRequest.findMany({
            where: {
                receiver: user.login42,
                status: 'accepted',
            }
        })

        if (friendSent) {
            for (let i in friendSent) {
                const friendUser = await prisma.user.findFirst({
                    where: {
                        login42: friendSent[i].receiver,
                    }
                })
                if (friendUser)
                    this.insertFriend(friendUser.username, friendUser.imagePath, friendUser.userStatus, friendList);
            }
        }

        if (friendReceived) {
            for (let i in friendReceived) {
                const friendUser = await prisma.user.findFirst({
                    where: {
                        login42: friendReceived[i].sender,
                    }
                })
                if (friendUser)
                    this.insertFriend(friendUser.username, friendUser.imagePath, friendUser.userStatus, friendList);
            }
        }

        // Get the match history and stats of the user
        const matchLeft = await prisma.game.findMany({
            where: {
                leftPlayer: user.login42,
                active: false,
            },
        })

        const matchRight = await prisma.game.findMany({
            where: {
                rightPlayer: user.login42,
                active: false,
            },
        })

        let leftPlayed = matchLeft.length;
        let leftWin = 0;
        let rightPlayed = matchRight.length;
        let rightWin = 0;

        if (matchLeft) {
            for (let i in matchLeft) {
                if (matchLeft[i].winner == user.login42)
                    leftWin = leftWin + 1;
                const adversaire = await prisma.user.findFirst({
                    where: {
                        login42: matchLeft[i].rightPlayer,
                    },
                })
                if (adversaire) {
                    this.insertMatch(user.username, user.imagePath,
                        matchLeft[i].leftPlayerScore, adversaire.username,
                        adversaire.imagePath, matchLeft[i].rightPlayerScore,
                        matchLeft[i].winner, matchLeft[i].updatedAt, matchHistory);
                }
            }
        }

        if (matchRight) {
            for (let i in matchRight) {
                if (matchRight[i].winner == user.username)
                    rightWin = rightWin + 1;
                const adversaire = await prisma.user.findFirst({
                    where: {
                        login42: matchRight[i].leftPlayer,
                    },
                })
                if (adversaire) {
                    this.insertMatch(adversaire.username,
                        adversaire.imagePath, matchRight[i].leftPlayerScore, user.username, user.imagePath,
                        matchRight[i].rightPlayerScore, matchRight[i].winner, matchRight[i].updatedAt, matchHistory);
                }
            }
        }

        let played = leftPlayed + rightPlayed;
        let win = leftWin + rightWin;
        let winRatio = win / played;
        let letfWinRatio = leftWin / leftPlayed;
        let rightWinRatio = rightWin / rightPlayed;

        const stats = new StatisticsDto(played, win, winRatio, rightPlayed,
            rightWin, rightWinRatio, leftPlayed, leftWin, letfWinRatio);

        // Order match in chronologic order
        let x = 0;
        let longeur = matchHistory.length;
        while (x < longeur) {
            if (x !== longeur - 1 && matchHistory[x].updatedAt < matchHistory[x + 1].updatedAt) {
                let temp = matchHistory[x];
                matchHistory[x] = matchHistory[x + 1];
                matchHistory[x + 1] = temp;
                x = 0;
            }
            else {
                x = x + 1;
            }
        }
        // At last, return the ProfileResponse
        return new PublicProfileDto(false, user.username, user.userStatus, user.imagePath,
            friendList, matchHistory, stats, goingto);
    }

    async getProfileEdit(login42: string): Promise<PrivateProfileDto> {
        // Create prisma client and look if the username exist in the database
        let user;

        try {
            user = await prisma.user.findUnique({
                where: {
                    login42: login42
                }
            })
        }
        catch { }

        //  If he dosen't exist, return error true and everything at null
        if (!user) {
            return new PrivateProfileDto(true, null, null, null, null, null, null, null, null, await this.getBlockedUsers(login42), "none");
        }

        //  Free the array's from previous values
        let friendList: FriendDto[] = [];
        let friendRequests: FriendRequestDto[] = [];
        let matchHistory: MatchDto[] = [];

        //  Build the response

        //  Get friends of user
        const friendSent = await prisma.friendRequest.findMany({
            where: {
                sender: user.login42,
                status: 'accepted',
            }
        })

        const friendReceived = await prisma.friendRequest.findMany({
            where: {
                receiver: user.login42,
                status: 'accepted',
            }
        })

        if (friendSent) {
            for (let i in friendSent) {
                const friendUser = await prisma.user.findFirst({
                    where: {
                        login42: friendSent[i].receiver,
                    }
                })
                if (friendUser)
                    this.insertFriend(friendUser.username, friendUser.imagePath, friendUser.userStatus, friendList);
            }
        }

        if (friendReceived) {
            for (let i in friendReceived) {
                const friendUser = await prisma.user.findFirst({
                    where: {
                        login42: friendReceived[i].sender,
                    }
                })
                if (friendUser)
                    this.insertFriend(friendUser.username, friendUser.imagePath, friendUser.userStatus, friendList);
            }
        }

        // Get friend request's received by the user

        const friendReqs = await prisma.friendRequest.findMany({
            where:
            {
                receiver: user.login42,
                status: 'pending',
            },
        })

        if (friendReqs) {
            for (let i in friendReqs) {
                const senderUser = await prisma.user.findFirst({
                    where: {
                        login42: friendReqs[i].sender,
                    }
                })
                if (senderUser)
                    this.insertFriendRequest(senderUser.username, senderUser.imagePath, friendRequests);
            }
        }


        // Get the match history and stats of the user
        const matchLeft = await prisma.game.findMany({
            where: {
                leftPlayer: user.login42,
                active: false,
            },
        })

        const matchRight = await prisma.game.findMany({
            where: {
                rightPlayer: user.login42,
                active: false,
            },
        })

        let leftPlayed = matchLeft.length;
        let leftWin = 0;
        let rightPlayed = matchRight.length;
        let rightWin = 0;

        if (matchLeft) {
            for (let i in matchLeft) {
                if (matchLeft[i].winner == user.login42)
                    leftWin = leftWin + 1;
                const adversaire = await prisma.user.findFirst({
                    where: {
                        login42: matchLeft[i].rightPlayer,
                    },
                })
                if (adversaire) {
                    this.insertMatch(user.username, user.imagePath,
                        matchLeft[i].leftPlayerScore, adversaire.username,
                        adversaire.imagePath, matchLeft[i].rightPlayerScore,
                        matchLeft[i].winner, matchLeft[i].updatedAt, matchHistory);
                }
            }
        }

        if (matchRight) {
            for (let i in matchRight) {
                if (matchRight[i].winner == user.username)
                    rightWin = rightWin + 1;
                const adversaire = await prisma.user.findFirst({
                    where: {
                        login42: matchRight[i].leftPlayer,
                    },
                })
                if (adversaire) {
                    this.insertMatch(adversaire.username,
                        adversaire.imagePath, matchRight[i].leftPlayerScore, user.username, user.imagePath,
                        matchRight[i].rightPlayerScore, matchRight[i].winner, matchRight[i].updatedAt, matchHistory);
                }
            }
        }

        let played = leftPlayed + rightPlayed;
        let win = leftWin + rightWin;
        let winRatio = win / played;
        let letfWinRatio = leftWin / leftPlayed;
        let rightWinRatio = rightWin / rightPlayed;

        const stats = new StatisticsDto(played, win, winRatio, rightPlayed,
            rightWin, rightWinRatio, leftPlayed, leftWin, letfWinRatio);

        // Order match in chronologic order
        let x = 0;
        let longeur = matchHistory.length;
        while (x < longeur) {
            if (x !== longeur - 1 && matchHistory[x].updatedAt < matchHistory[x + 1].updatedAt) {
                let temp = matchHistory[x];
                matchHistory[x] = matchHistory[x + 1];
                matchHistory[x + 1] = temp;
                x = 0;
            }
            else {
                x = x + 1;
            }
        }

        // At last, return the ProfileResponse
        var blockL = await this.getBlockedUsers(login42);

        return new PrivateProfileDto(false, user.username, user.userStatus, user.imagePath,
            friendList, friendRequests, matchHistory, stats, user.authenticator, blockL, user.username);
    }

    async updateUsername(newUsername: string, login42: string): Promise<responseDefault> {
        let response = new responseDefault(true, "Username change to " + newUsername + " successful.")

        //  Find the user to update to
        const user = await prisma.user.findUnique({
            where: {
                login42: login42,
            },
        })
        if (!user) {
            response.message = "Update username Error 00: Unauthorised client."
            return (response);
        }

        //  Parse username for valid entry
        if (newUsername.length < 5) {
            response.message = "Update username Error 01: Username must have more than 4 character's."
            return (response);
        }

        if (newUsername.length > 12) {
            response.message = "Update username Error 02: Username max number of character's is 12."
            return (response)
        }

        try
        {
            let userExist = await prisma.user.findUnique({
                where : {
                    username: newUsername
                }
            })

            if (userExist)
            {
                response.message = "Update username Error 03: Username already taken.";
                return (response);
            }
        }
        catch{}

        //  Put the username with a capital first letter and the rest in lowercase
        newUsername = newUsername.toLowerCase();
        try {
            await prisma.user.update({
                where: {
                    login42: login42
                },
                data: {
                    username: newUsername,
                }
            })
        }
        catch
        {
            response.message = "Update username Error 04: Username change failed due to database update error."
            return (response);
        }

        response.error = false;
        return (response);
    }

    async getPhoto(login42: string): Promise<responseDefault> {
        let response = new responseDefault(true, "/defaultPhoto.png");
        let user;

        try {
            user = await prisma.user.findUnique({
                where: { login42: login42 }
            })
        }
        catch { }

        if (user != undefined) {
            response.message = user.imagePath;
            response.error = false;
        }
        return (response);
    }

    async getAuth(login42: string): Promise<responseDefault> {
        let response = new responseDefault(false, "inactive");
        let user;

        try {
            user = await prisma.user.findUnique(
                {
                    where: { login42: login42 }
                })
        }
        catch { }

        if (user != undefined) {
            if (user.authenticator == true) {
                response.message = "active";
                return (response)
            }
        }
        return (response);
    }

    async getActiveGames(): Promise<ActiveGameDto> {
        let array: Game[] = [];
        let games;
        let leftPlayer;
        let rightPlayer

        //  Get every active games
        try {
            games = await prisma.game.findMany({
                where: {
                    active: true
                }
            })
        }
        catch { }

        //  If there is some active games, insert them in an array of games
        if (games) {
            for (let i in games) {
                //  Set both player to undefined

                leftPlayer = undefined;
                rightPlayer = undefined;

                //  Try to Find left Player
                try {
                    leftPlayer = await prisma.user.findUnique({
                        where: {
                            login42: games[i].leftPlayer
                        }
                    })
                } catch { }

                //  Try to find right player
                try {
                    rightPlayer = await prisma.user.findUnique({
                        where: {
                            login42: games[i].rightPlayer
                        }
                    })
                } catch { }

                //  Add the game to the array if both player are found in the database
                if (leftPlayer != undefined && rightPlayer != undefined) {
                    let newGame = new Game(leftPlayer.username, leftPlayer.imagePath, rightPlayer.username, rightPlayer.imagePath, games[i].gameRoomID);
                    array.push(newGame);
                }
            }
        }

        //  Create the Active game data object with the array and return it.
        const response = new ActiveGameDto(array);
        return (response);
    }

    async getBlockedUsers(login42: string): Promise<BlockDto []> {
        let array: BlockDto[] = [];
        let blockArray;

        //  Get every active games
        try {
            blockArray = await prisma.block.findMany({
                where: {
                    blocker: login42
                }
            })
        }
        catch {}

        //  If there is some active games, insert them in an array of games
        if (blockArray) {
            for (let i in blockArray) {
                //  Set both player to undefined

                var blocked;

                //  Try to Find left user
                try {
                    blocked = await prisma.user.findUnique({
                        where: {
                            login42: blockArray[i].blocked
                        }
                    })
                } catch { }

                //  Add the game to the array if both player are found in the database
                if (blocked != undefined && login42 != undefined)
                {
                    let r = (Math.random() + 1).toString(36).substring(2);
                    let newBlock = new BlockDto(blocked.username, blocked.imagePath, r);
                    array.push(newBlock);
                }
            }
        }

        //  Create the Active game data object with the array and return it.
        return (array);
    }

    async updatePhoto(newFilePath: string, login42: string): Promise<responseUploadPhoto> {
        let response = new responseUploadPhoto(true, "Photo upload successful", "not changed");

        const user = await prisma.user.findUnique({
            where: {
                login42: login42,
            },
        })

        if (!user) {
            response.message = "Upload photo Error 00: Unauthorised client"
            return (response);
        }
        const path = "/" + newFilePath;
        try {
            await prisma.user.update({
                where: {
                    login42: login42,
                },
                data: {
                    imagePath: path,
                }
            })
            response.error = false;
            response.photo = path;
            return (response);
        }
        catch
        {
            response.message = "Upload photo Error 01: Upload photo in database failed."
            return (response);
        }
    }

    async addFriend(login42: string, newFriend: string) {

        //  First, find the login42 linked with the newFriend username
        let user;

        try {
            user = await prisma.user.findUnique({
                where: {
                    username: newFriend
                }
            })

            //  If the user dosent exist, return 
            if (!user) {
                return;
            }
        }
        catch { }

        //  Then look if the two user pair in friend request already exist 
        try {
            let requestExist = await prisma.friendRequest.findUnique({
                where: {
                    sender_receiver: {
                        sender: login42,
                        receiver: user.login42
                    }
                }
            })

            if (requestExist) {
                return;
            }

            if (!requestExist) {
                let requestExist = await prisma.friendRequest.findUnique({
                    where: {
                        sender_receiver: {
                            sender: user.login42,
                            receiver: login42
                        }
                    }
                })

                if (requestExist) {
                    await prisma.friendRequest.update({
                        where:
                        {
                            sender_receiver: {
                                sender: user.login42,
                                receiver: login42
                            }
                        },
                        data: {
                            status: "accepted"
                        }
                    })
                    requestExist.status = "accepted"
                    return;
                }

                await prisma.friendRequest.create({
                    data: {
                        sender: login42,
                        receiver: user.login42
                    }
                })

            }
        }
        catch { }

        //  If we are here, the request dosen't exist so lets create it
        try {
            await prisma.friendRequest.create({
                data: {
                    sender: login42,
                    receiver: user.username
                }
            })
        }
        catch { }
    }

    async removeFriend(login42: string, oldFriend:string)
    {
        //  First, find the login42 linked with the oldfriend username
        let user;
        
        try
        {
            user = await prisma.user.findUnique({
                where: {
                    username: oldFriend
                }})

            //  If the user dosent exist, return 
            if (!user)
            {
                return;
            }
        }
        catch {return;}

     //  Then look if the two user pair in friend request already exist 
        try
        {
            let requestExist = await prisma.friendRequest.findUnique({
                where: {
                    sender_receiver:
                    {
                        sender: login42,
                        receiver: user.login42
                    }}})

            if (requestExist)
            {
                await prisma.friendRequest.delete({
                    where:
                    {
                        sender_receiver:
                        {
                            sender: login42,
                            receiver: user.login42
                        }
                    }
                })
                return;
            }

            if (!requestExist)
            {
                let requestExist = await prisma.friendRequest.findUnique({
                    where:
                    {
                        sender_receiver:
                        {
                            sender: user.login42,
                            receiver: login42
                        }
                    }})

             if (requestExist)
             {
                await prisma.friendRequest.delete({
                    where:
                    {
                        sender_receiver:
                        {
                            sender: user.login42,
                            receiver: login42
                        }
                    }
                })
                return;
             }
         }
     }
     catch {return}
    }

    async denyRequest(login42: string, sender: string) {
        //  First, find the login42 linked with the newFriend username
        let user;

        try {
            user = await prisma.user.findUnique({
                where: {
                    username: sender
                }
            })

            //  If the user dosent exist, return 
            if (!user) {
                return;
            }
        }
        catch { }

        //  Then, we look for the request this username -> login42 has sent an deny it
        try {
            let requestExist = await prisma.friendRequest.findUnique({
                where: {
                    sender_receiver: {
                        sender: user.login42,
                        receiver: login42
                    }
                }
            })

            //  Then we change the request status to denied
            if (requestExist) {
                await prisma.friendRequest.update({
                    where: {
                        sender_receiver: {
                            sender: user.login42,
                            receiver: login42
                        }
                    },
                    data: {
                        status: "declined",
                    }
                })
            }
        }
        catch { }
        return;
    }

    async blockUser(login42: string, userToBlock: string) {
        //  First, find the user associated with userToBlock
        let user;

        try {
            user = await prisma.user.findUnique({
                where: {
                    username: userToBlock
                }
            })

            //  If the user dosent exist, return
            if (!user) {
                return;
            }
        }
        catch { }

        //  Create a block rule in the database
        try {
            await prisma.block.create({
                data: {
                    blocker: login42,
                    blocked: user.login42
                }
            })
        }
        catch { }
    }

    async unblockUser(login42: string, userToUnblock: string)
    {
        //  First, find the user associated with userToBlock
        let user;

        try {
            user = await prisma.user.findUnique({
                where: {
                    username: userToUnblock
                }
            })

            //  If the user dosent exist, return
            if (!user) {
                return;
            }
        }
        catch {return;}

        //  remove the block rule in the database
        try
        {
            await prisma.block.delete({
                where: {
                    blocker_blocked: {
                        blocker: login42,
                        blocked: user.login42
                    }
                }
            })
        }
        catch {return;}
    }

    async getUserId(login42: string): Promise<{ userid: number }> | undefined {
        let user;

        try {
            user = await prisma.user.findUnique({
                where: { login42: login42 }
            })
        }
        catch { }

        if (user) {
            return ({ userid: user.userID });
        }
        return ({userid: 999});
    }

    async getSinglePlayerData(login42: string): Promise<{ login: string, photo: string }> | null {
        type User = {
            username: string,
            imagePath: string
        }
        let user: User;

        try {
            user = await prisma.user.findUnique({
                where: { login42: login42 }
            })
        }
        catch { }

        if (user) {
            let login = user.username;
            let photo = user.imagePath;
            return ({
                login: login,
                photo: photo
            });
        }
        return (null);
    }

     // Utility Method to get dto from entity
//   private entityToDto(user: User): PrivateProfileDto {
//     const userDto = new UserDto();

//     userDto.userID = user.userID;
//     userDto.login42 = user.login42;
//     userDto.username = user.username;
//     userDto.userStatus = user.userStatus;
//     // // userDto.friends = user.friendsofthisuser
//     //   ? user.friendsofthisuser.map((x) => this.entityToDto(x))
//     //   : [];
//     // userDto.blocked = user.blockedbythisuser
//     //   ? user.blockedbythisuser.map((x) => this.entityToDto(x))
//     //   : [];
//     userDto.authenticator = user.authenticator;
//     userDto.imagePath = user.imagePath;
//     return userDto;
//   }

  // Find one user by id
  public async findOneById(id: string) {
    // const user: User = await prisma.user.findUnique({
    //   where: { userID: id },
    //   //include: { userFriends: true },
    // });
    // if (!user) return null;
    const userDto: PrivateProfileDto = await this.getProfileEdit(id);
    return userDto;
  }

  public async setStatus(id: string, status: userStatus): Promise<PrivateProfileDto>
  {
	var user;

	try
	{
	    user = await prisma.user.findUnique({
			where: {
				login42: id 
			} 
		});
	}
	catch{}

    if (!user) {
      return null;
    }
    const updatedUser = await prisma.user.update({
      where: { login42: id },
      data: { userStatus: status },
    });
    // convert the updated user object to a DTO
    const userDto = await this.getProfileEdit(updatedUser.login42);
    return userDto;
  }
}
