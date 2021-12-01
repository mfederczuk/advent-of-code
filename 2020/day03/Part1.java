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

public class Part1 {
	enum Field {
		TREE,
		NOT_TREE
	};

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

		int treeHitCount = 0;

		for(int i = 0; i < map.size(); ++i) {
			var row = map.get(i);
			int column = (i * 3) % row.size();

			var field = row.get(column);
			if(field == Field.TREE) ++treeHitCount;
		}

		System.out.println(treeHitCount);
	}
}
