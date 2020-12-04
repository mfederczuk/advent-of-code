/*
 * Advent of Code 2020 - Day 4 - Part 1
 * Copyright (C) 2020  Michael Federczuk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
