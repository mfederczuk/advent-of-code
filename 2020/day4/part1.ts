import { readFileSync } from "fs";

let inputFilePath = "part1_example_input";
if(process.argv.length >= 3) inputFilePath = process.argv[2];

const inputFile = readFileSync(inputFilePath).toString();

const passportKeysList = inputFile.split("\n\n").map((passportStr) => {
	return passportStr.trim().split(/\s+/).map((field) => (field.split(":")[0]));
});

const requiredFieldKeys = [
	"byr",
	"iyr",
	"eyr",
	"hgt",
	"hcl",
	"ecl",
	"pid"
];

const numOfValidPassports = passportKeysList.reduce((numOfValidPassports, passportKeys) => {
	if(requiredFieldKeys.every((requiredFieldKey) => (passportKeys.includes(requiredFieldKey)))) {
		++numOfValidPassports;
	}

	return numOfValidPassports;
}, 0);

console.log(numOfValidPassports);
