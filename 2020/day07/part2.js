/*
 * Advent of Code 2020 - Day 7 - Part 2
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

let inputFilePath = "example_input_1";
if(process.argv.length >= 3) inputFilePath = process.argv[2];

const inputFile = readFileSync(inputFilePath).toString();

String.prototype.removeSuffix = function(suffix) {
	if(suffix instanceof RegExp) {
		const match = this.match(suffix);
		if(match.groups["suffix"]) {
			return this.substring(0, this.length - match.groups["suffix"].length);
		}
	} else if(this.endsWith(suffix)) {
		return this.substring(0, this.length - suffix.length);
	}

	return this;
};

/**
 * {
 *     [color: string]: [amount: number, color: string][]
 * }
 */
const bags = inputFile.trim()
		.split("\n")
		.map((s) => (s.removeSuffix(".")))
		.reduce((bags, s) => {
			const match = s.match(/^(?<bag>.*) bags contain (?<childBags>.*)$/);

			const childBags = match.groups["childBags"]
					.split(", ")
					.map((s) => (s.removeSuffix(/(?<suffix> bag(s)?)$/)))
					.reduce((childBags, s) => {
						const match = s.match(/^(?<amount>\d+) (?<color>.*)$/);
						if(match !== null) {
							childBags.push([
								Number(match.groups["amount"]),
								match.groups["color"]
							]);
						}
						return childBags;
					}, []);

			bags[match.groups["bag"]] = childBags;
			return bags;
		}, {});

const ourBagColor = "shiny gold";

/*
 * I'm sure that there is a better way to do it, but I'm to lazy to keep working on it.
 * It works, that's all that matters.
 */
function countBags(accumulator, bagColor) {
	const childBags = bags[bagColor];
	childBags.forEach((childBag) => {
		for(let i = 0; i < childBag[0]; ++i) {
			++accumulator;
			accumulator = countBags(accumulator, childBag[1]);
		}
	});
	return accumulator;
}

console.log(countBags(0, ourBagColor));
