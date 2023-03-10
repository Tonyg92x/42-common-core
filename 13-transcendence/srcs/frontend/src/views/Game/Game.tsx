import ReactiveCanvas from './components/ReactiveCanvas'
import {usersocket} from "./Matchmaking"

var onlyonce = 0; //prevent functions being called twice

function prepareGame()
{
    usersocket.emit("playerReady");
}

export default function Game()
{
    prepareGame();
    onlyonce = 1;
    return <ReactiveCanvas />
}

