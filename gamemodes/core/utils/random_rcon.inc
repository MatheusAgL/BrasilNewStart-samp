// Random RCON in start-server:
static RconPassword[50];

stock Rcon_GetPassword() {
	new str[20];

	format(str, sizeof(str), RconPassword);

	return str;
}

stock Rcon_SetPassword(const password[]) {

	format(RconPassword, sizeof(RconPassword), "%s", password);

	new string[50];
	format(string, sizeof(string), "rcon_password %s", password);

	SendRconCommand(string);
}

#define strrand(%0,%1) (random(%1 - %0 + 1) + %0)

stock Rcon_GetRandPass() {
	new str[20];

	format(str, sizeof(str), "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
	strrand('A','Z'), strrand('A','Z'), strrand('1','9'), strrand('A','Z'), strrand('A','Z'),
	strrand('A','Z'), strrand('1','9'), strrand('A','Z'), strrand('A','Z'), strrand('1','9'),
	strrand('1','9'), strrand('A','Z'), strrand('A','Z'), strrand('A','Z'), strrand('1','9'), 
	strrand('A','Z'), strrand('1','9'), strrand('A','Z'), strrand('1','9'));

	return str;
}
