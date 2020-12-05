/*
 * Advent of Code 2020 - Day 4 - Part 2
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
import { MapLike } from "typescript";

let inputFilePath = "part2_example_input_valid";
if(process.argv.length >= 3) inputFilePath = process.argv[2];

const inputFile = readFileSync(inputFilePath).toString();

const passports = inputFile.split("\n\n").map((passportStr) => {
	return passportStr.trim().split(/\s+/).reduce((passportObj, field) => {
		const [key, value] = field.split(":");
		passportObj[key] = value;
		return passportObj;
	}, {} as MapLike<string>);
});

const validEyeColors = [
	"amb",
	"blu",
	"brn",
	"gry",
	"grn",
	"hzl",
	"oth"
];

const requiredFieldValidators: [string, (value: string) => boolean][] = [
	["byr", (value) => {
		if(value.match(/^[0-9]{4}$/) == null) return false;
		const byr = Number(value);
		return (byr >= 1920 && byr <= 2002);
	}],
	["iyr", (value) => {
		if(value.match(/^[0-9]{4}$/) == null) return false;
		const iyr = Number(value);
		return (iyr >= 2010 && iyr <= 2020);
	}],
	["eyr", (value) => {
		if(value.match(/^[0-9]{4}$/) == null) return false;
		const eyr = Number(value);
		return (eyr >= 2020 && eyr <= 2030);
	}],
	["hgt", (value) => {
		const match = value.match(/^(?<hgtStr>[0-9]+)(?<unit>cm|in)$/);
		if(match === null) return false;

		const { hgtStr, unit } = match.groups!!;
		const hgt = Number(hgtStr);

		switch(unit) {
			case("cm"): return (hgt >= 150 && hgt <= 193);
			case("in"): return (hgt >= 59 && hgt <= 76);
		}
		throw undefined;
	}],
	["hcl", (value) => (value.match(/^#[0-9a-f]{6}$/) != null)],
	["ecl", (value) => (validEyeColors.includes(value))],
	["pid", (value) => (value.match(/^[0-9]{9}$/) != null)]
];

const numOfValidPassports = passports.reduce((numOfValidPassports, passport) => {
	const passportValid = requiredFieldValidators.every(([requiredFieldKey, requiredFieldValidator]) => {
		const fieldValue = passport[requiredFieldKey];
		return (fieldValue !== undefined && requiredFieldValidator(fieldValue));
	});

	if(passportValid) ++numOfValidPassports;

	return numOfValidPassports;
}, 0);

console.log(numOfValidPassports);
