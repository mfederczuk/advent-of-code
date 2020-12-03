/*
 * Advent of Code 2020 - Day 3 - Part 2
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

import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Part2 {
	enum Field {
		TREE,
		NOT_TREE
	};

	static class Slope {
		public int right;
		public int down;

		public Slope(int right, int down) {
			this.right = right;
			this.down = down;
		}
	}

	public static void main(String[] args) throws IOException {
		String inputFile = "example_input";
		if(args.length >= 1) inputFile = args[0];

		List<List<Field>> map = new ArrayList<List<Field>>();

		var inputFileScanner = new Scanner(new FileInputStream(inputFile));

		while(inputFileScanner.hasNext()) {
			var line = inputFileScanner.nextLine();

			var row = new ArrayList<Field>();
			map.add(row);

			for(char ch : line.toCharArray()) {
				var field = (ch == '#' ? Field.TREE : Field.NOT_TREE);
				row.add(field);
			}
		}

		inputFileScanner.close();

		List<Slope> slopes = new ArrayList<Slope>();
		slopes.add(new Slope(1, 1));
		slopes.add(new Slope(3, 1));
		slopes.add(new Slope(5, 1));
		slopes.add(new Slope(7, 1));
		slopes.add(new Slope(1, 2));

		long treeHitCount = 1;

		for(var slope : slopes) {
			int slopeTreeHitCount = 0;

			for(int i = 0, rowIndex; (rowIndex = (i * slope.down)) < map.size(); ++i) {
				var row = map.get(rowIndex);
				int columnIndex = (i * slope.right) % row.size();

				var field = row.get(columnIndex);
				if(field == Field.TREE) ++slopeTreeHitCount;
			}

			treeHitCount *= slopeTreeHitCount;
		}

		System.out.println(treeHitCount);
	}
}
