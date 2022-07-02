int generate1To100() {
	// Use the analog value of A0 pin as a random seed
	randomSeed(analogRead(A0));
	return random(1, 100);
}

void askMathQuestion() {
	// TODO
	;;
}