import { Injectable } from '@nestjs/common';
import { UpdateGameDto, GamePlayerDto, BallDto } from '../dtos/gameUpdate.dtos';

export interface UpdateProp {
	keyActions: {
		up: boolean,
		down: boolean
	}
}

export interface UpdateProps{
	keyActionsPlayer1:UpdateProp,
	keyActionsPlayer2:UpdateProp
}

@Injectable()
export class GameUpdate
{
	leftPlayer: GamePlayerDto;
	rightPlayer:GamePlayerDto;
	gameBall: BallDto;
	updateGame:UpdateGameDto;

	constructor() {
		this.leftPlayer = new GamePlayerDto('', '', 0, 0.5)
		this.rightPlayer = new GamePlayerDto('', '', 0, 0.5)
		this.gameBall = new BallDto(0.5, 0.5, 0.01, 10, -1, 0)
		this.updateGame = new UpdateGameDto(this.leftPlayer, this.rightPlayer, this.gameBall, false, '')
	}
	public createUpdateGameDto(){ //to recreate a new updateGame after the two players are changed
		this.updateGame = new UpdateGameDto(this.leftPlayer, this.rightPlayer, this.gameBall, false, '')
	}
	update = ({ keyActionsPlayer1, keyActionsPlayer2}: UpdateProps) => {
		const playerHeight = 0.15
		const playerWidth = 0.01
	
		if (this.leftPlayer.playerPos > 0 && keyActionsPlayer1.keyActions.up)
			this.leftPlayer.playerPos -= 0.01
		if (this.leftPlayer.playerPos < 1 && keyActionsPlayer1.keyActions.down)
			this.leftPlayer.playerPos += 0.01
		
		if (this.rightPlayer.playerPos > 0 && keyActionsPlayer2.keyActions.up)
			this.rightPlayer.playerPos -= 0.01
		if (this.rightPlayer.playerPos < 1 && keyActionsPlayer2.keyActions.down)
			this.rightPlayer.playerPos += 0.01
	
		//this.rightPlayer.playerPos += (this.gameBall.ballPosY - this.rightPlayer.playerPos) * 0.1 //used only for localplay
	
		this.gameBall.ballPosX += (this.gameBall.ballDirX * this.gameBall.ballSpeed) / 1000
		this.gameBall.ballPosY += (this.gameBall.ballDirY * this.gameBall.ballSpeed) / 1000
	
		if (this.gameBall.ballPosY <= 0.01 || this.gameBall.ballPosY >= 0.99) {
			this.gameBall.ballDirY = -this.gameBall.ballDirY
		}
	
		let player = this.gameBall.ballPosX < 0.5 ? this.leftPlayer : this.rightPlayer
	
		let bTop, bBottom, bLeft, bRight
		let pTop, pBottom, pLeft, pRight
	
		bTop = this.gameBall.ballPosY - (this.gameBall.ballRadius / 3 * 2)
		bBottom = this.gameBall.ballPosY + (this.gameBall.ballRadius / 3 * 2)
		bLeft = this.gameBall.ballPosX - this.gameBall.ballRadius
		bRight = this.gameBall.ballPosX + this.gameBall.ballRadius
	
		pTop = player.playerPos - (playerHeight / 2)
		pBottom = player.playerPos + (playerHeight / 2)
		pLeft = (player === this.leftPlayer) ? 0 : 1 - playerWidth
		pRight = (player === this.leftPlayer) ? playerWidth : 1
	
		if (pLeft < bRight && pTop < bBottom && pRight > bLeft && pBottom > bTop) {
			let collidePoint = this.gameBall.ballPosY - player.playerPos
			collidePoint = collidePoint / (playerHeight / 2)
	
			let angleRad = (Math.PI / 4) * collidePoint
	
			let direction = this.gameBall.ballPosX < 0.5 ? 1 : -1
	
			this.gameBall.ballDirX = direction * Math.cos(angleRad)
			this.gameBall.ballDirY = Math.sin(angleRad)
		} else if (this.gameBall.ballPosX <= this.gameBall.ballRadius || this.gameBall.ballPosX + this.gameBall.ballRadius >= 1) {
			if (this.gameBall.ballPosX > 0.5) this.leftPlayer.playerScore++
			else this.rightPlayer.playerScore++
			this.gameBall.ballPosX = 0.5
			this.gameBall.ballPosY = 0.5
			this.gameBall.ballSpeed = 10.0
			this.gameBall.ballDirX = this.gameBall.ballDirY < 0 ? 1.0 : -1.0
			this.gameBall.ballDirY = 0.0
			this.leftPlayer.playerPos = 0.5
			this.rightPlayer.playerPos = 0.5
		}
	}
	public updateGameUpdateDto(){
		this.updateGame.gameBall = this.gameBall;
		this.updateGame.leftPlayer = this.leftPlayer;
		this.updateGame.rightPlayer = this.rightPlayer;
	}
}
