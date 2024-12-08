type Position = {
  x: number;
  y: number;
};

type Map = {
  raw: string[][];
  width: number;
  height: number;
};

function _add_position(p1: Position, p2: Position): Position {
  return {
    x: p1.x + p2.x,
    y: p1.y + p2.y,
  };
}

function _set_to_array<T>(set: Set<string>): T[] {
  const tmp: T[] = [];
  for (const antinode of set) {
    tmp.push(JSON.parse(antinode) as T);
  }
  return tmp;
}

const get_antenas = (map: Map) => {
  const antena_map: Record<string, Position[]> = {};

  for (let i = 0; i < map.height; i++) {
    for (let j = 0; j < map.width; j++) {
      const raw = map.raw;
      if (raw[i][j] === '.' || raw[i][j] === '#') {
        continue;
      }
      antena_map[raw[i][j]] = [
        ...(antena_map[raw[i][j]] || []),
        { x: j, y: i },
      ];
    }
  }

  return antena_map;
};

const project_antinode = (map: Map, pair: Position[]): Position[] | null => {
  const a1 = pair[0];
  const a2 = pair[1];

  const antinodes: Position[] = [];
  let i = 0;

  for (const antenna of pair) {
    const other = i++ === 0 ? a2 : a1;
    const dir_vec: Position = {
      x: other.x - antenna.x,
      y: other.y - antenna.y,
    };
    const antinode_pos_vec: Position = { x: -dir_vec.x, y: -dir_vec.y };
    const antinode_pos: Position = _add_position(antenna, antinode_pos_vec);

    if (
      antinode_pos.x < 0 ||
      antinode_pos.x > map.width - 1 ||
      antinode_pos.y < 0 ||
      antinode_pos.y > map.height - 1
    ) {
      // Out of bounds
      continue;
    }

    antinodes.push(antinode_pos);
  }

  return antinodes;
};

const is_out_of_bounds = (pos: Position, map: Map) => {
  return (
    pos.x < 0 || pos.x > map.width - 1 || pos.y < 0 || pos.y > map.height - 1
  );
};

const project_antinode_p2 = (map: Map, pair: Position[]): Position[] | null => {
  const a1 = pair[0];
  const a2 = pair[1];

  const antinodes: Position[] = [];
  let i = 0;

  for (const antenna of pair) {
    antinodes.push(antenna);

    let other = i++ === 0 ? a2 : a1;
    const dir_vec: Position = {
      x: other.x - antenna.x,
      y: other.y - antenna.y,
    };
    const antinode_pos_vec: Position = { x: -dir_vec.x, y: -dir_vec.y };
    const antinode_pos: Position = _add_position(antenna, antinode_pos_vec);

    if (is_out_of_bounds(antinode_pos, map)) {
      // Out of bounds
      continue;
    }
    antinodes.push(antinode_pos);

    other = antenna;
    let new_antenna = antinode_pos;

    while (true) {
      const dir_vec: Position = {
        x: other.x - new_antenna.x,
        y: other.y - new_antenna.y,
      };
      const antinode_pos_vec: Position = { x: -dir_vec.x, y: -dir_vec.y };
      const antinode_pos: Position = _add_position(
        new_antenna,
        antinode_pos_vec
      );

      if (is_out_of_bounds(antinode_pos, map)) {
        // Out of bounds
        break;
      }

      antinodes.push(antinode_pos);
      other = new_antenna;
      new_antenna = antinode_pos;
    }
  }

  return antinodes;
};

const create_antinodes = (map: Map): Position[] => {
  const antinodes = new Set<string>();

  const antena_map = get_antenas(map);

  // Loop over all the positions
  for (const [_, positions] of Object.entries(antena_map)) {
    if (positions.length < 2) continue;

    for (let i = 0; i < positions.length; i++) {
      for (let j = i + 1; j < positions.length; j++) {
        const pair = [positions[i], positions[j]];
        const antinode_pos = project_antinode_p2(map, pair);
        if (antinode_pos != null) {
          for (const apos of antinode_pos) {
            antinodes.add(JSON.stringify(apos));
          }
        }
      }
    }
  }

  return _set_to_array<Position>(antinodes);
};

const main = async () => {
  const map_raw = await Deno.readTextFile('./src/08/input.txt');
  const map = map_raw.split('\n').map((row) => row.split(''));

  const antinodes = create_antinodes({
    raw: map,
    width: map[0].length,
    height: map.length,
  });

  console.log(antinodes.length);
};

main();
