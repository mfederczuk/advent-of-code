/*
 * Copyright (c) 2020 Michael Federczuk
 *
 * SPDX-License-Identifier: MPL-2.0 AND Apache-2.0
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
