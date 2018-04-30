const circle = "O";
const cross = "X";
var singleGame = true;
const winCombination = [
	[c1, c2, c3],
	[c4, c5, c6],
	[c7, c8, c9],
	[c1, c4, c7],
	[c2, c5, c8],
	[c3, c6, c9],
	[c1, c5, c9],
	[c3, c5, c7]
];
var winner;
var player = {
		0: circle,
		1: cross
}
var counter = 0;

function init() {
	let cells = $(".cell");
	for (let i = 0; i < cells.length; i++) {
		cells[i].innerText = "";
		cells[i].style.backgroundColor = "";
	}
	winner = undefined;
	counter = 0;
	$(".gameOver")[0].style.display = "none";
	$(".text")[0].innerText = "";
}

$(".replayButton").click(function() {
	init();
})

$(".cell").click(function() {
	if (canClick(this)) {
		this.innerText = player[counter%2];
		decideWin();
		counter++;
		aiMove();
	}
})

function canClick(cell) {
	if (cell.innerText == "") return true;
	else return false;
}

function aiMove() {
	let moves = aiFindCellAvailable();
	moves[0].innerText = cross;
	decideWin();
	counter++;
}

function aiFindCellAvailable() {
	let cellAvailable = new Array();
	let cells = $(".cell");
	for (let i = 0; i < cells.length; i++) {
		if (canClick(cells[i])) cellAvailable.push(cells[i]);
	}
	return cellAvailable;
}

function decideWin() {
	winCombination.forEach(function(win) {
		if (decideWhoWin(win, circle)) {
			winner = "0";
			return;
		}
		if (decideWhoWin(win, cross)) {
			winner = "1";
			return;
		}
	});
	if (winner == undefined && decideTie()) winner = "tie"; 
	if(winner) gameover(winner);
}

function decideWhoWin(winArray, symbol) {
	for (let i = 0; i < winArray.length; i++) {
		if (winArray[i].innerText != symbol) {
			return false;
		}
	}
	winArray.forEach(function(win) {
		win.style.backgroundColor = "green";
	});
	return true;
}

function decideTie() {
	let cells = $(".cell");
	for (let i = 0; i < cells.length; i++) {
		if (cells[i].innerText == "") return false;
	}
	return true;
}

function gameover(winner) {
	let winMessage;
	$(".gameOver")[0].style.display = "block";
	if (winner === "0") {
		winMessage = "Player 1 wins!";
	} else if (winner === "1") {
		winMessage = "Player 2 wins!";
	} else if (winner === "tie") {
		winMessage = "Tie Game!"
	}
	$(".text")[0].innerText = winMessage;
}