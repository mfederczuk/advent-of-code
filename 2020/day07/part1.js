/*
 * Copyright (c) 2020 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
 */

/*
 * I'mma be honest, I don't try to make the cleanest solutions, I really just try to get things working, but this one,
 * in my opinion, is my worst one so far.
 * Yet it works. _Somehow_.
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
const colorsToSearch = [ourBagColor];

let foundNewColor;
do {
	foundNewColor = false;

	Object.entries(bags).forEach(([bagColor, childBags]) => {
		const foundColor = childBags.find(([, childBagColor]) => (colorsToSearch.includes(childBagColor) && !colorsToSearch.includes(bagColor)));
		if(foundColor !== undefined) {
			colorsToSearch.push(bagColor);
			foundNewColor = true;
		}
	});
} while(foundNewColor);

console.log(colorsToSearch.length - 1);
