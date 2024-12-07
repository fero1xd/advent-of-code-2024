const map_raw = await Deno.readTextFile('./src/06/sample.txt');
const map = map_raw.split('\n').map((row) => row.split(''));
map.pop();

const width = map[0].length;
const height = map.length;

type Direction = {
  x: number;
  y: number;
};

type Position = Direction;

const directions: Direction[] = [
  // Up
  { x: 0, y: -1 },
  // Right
  { x: 1, y: 0 },
  // Down
  { x: 0, y: 1 },
  // Left
  { x: -1, y: 0 },
];

function get_visited_path(): {
  starting_pos: Position;
  starting_dir: number;
  visited: Set<Position>;
} | null {
  let guard_dir: number = -1;
  let guard_pos: Position | null = null;
  let s_guard_dir: number = -1;
  let s_guard_pos: Position | null = null;

  for (let i = 0; i < height; i++) {
    for (let j = 0; j < width; j++) {
      if ('<>^v'.includes(map[i][j])) {
        guard_dir = '^>v<'.indexOf(map[i][j]);
        s_guard_dir = '^>v<'.indexOf(map[i][j]);
        s_guard_pos = {
          x: j,
          y: i,
        };
        guard_pos = {
          x: j,
          y: i,
        };
        break;
      }
    }

    if (guard_pos != null) {
      break;
    }
  }

  const visited_pos = new Set<string>();
  if (guard_dir < 0 || guard_pos == null) {
    return null;
  }
  visited_pos.add(JSON.stringify(guard_pos));

  while (true) {
    const curr_dir = directions[guard_dir];
    // 4, 6
    const new_pos: Position = {
      x: guard_pos.x + curr_dir.x,
      y: guard_pos.y + curr_dir.y,
    };

    if (
      new_pos.x < 0 ||
      new_pos.x > width - 1 ||
      new_pos.y < 0 ||
      new_pos.y > height - 1
    ) {
      // guard out of bounds
      break;
    }

    if (map[new_pos.y][new_pos.x] === '#') {
      guard_dir = (guard_dir + 1) % 4;
    } else {
      guard_pos = new_pos;
      visited_pos.add(JSON.stringify(guard_pos));
    }
  }

  const tmp = new Set<Position>();
  for (const str of visited_pos) {
    tmp.add(JSON.parse(str));
  }

  return {
    visited: tmp,
    starting_pos: s_guard_pos!,
    starting_dir: s_guard_dir,
  };
}

const check_loop = (
  obs_pos: Position,
  starting_pos: Position,
  starting_dir: number
): boolean => {
  let guard_dir = starting_dir;
  let guard_pos = starting_pos;

  const visited_with_dir = new Set<string>();
  visited_with_dir.add(JSON.stringify({ guard_pos, guard_dir }));

  if (map[obs_pos.y][obs_pos.x] === '#') {
    return false;
  }

  // Place a guard
  map[obs_pos.y][obs_pos.x] = '#';

  while (true) {
    const curr_dir = directions[guard_dir];
    // 4, 6
    const new_pos: Position = {
      x: guard_pos.x + curr_dir.x,
      y: guard_pos.y + curr_dir.y,
    };

    if (
      new_pos.x < 0 ||
      new_pos.x > width - 1 ||
      new_pos.y < 0 ||
      new_pos.y > height - 1
    ) {
      // guard out of bounds

      map[obs_pos.y][obs_pos.x] = '.';
      return false;
    }

    if (map[new_pos.y][new_pos.x] === '#') {
      guard_dir = (guard_dir + 1) % 4;
    } else {
      guard_pos = new_pos;
    }

    if (visited_with_dir.has(JSON.stringify({ guard_pos, guard_dir }))) {
      map[obs_pos.y][obs_pos.x] = '.';
      return true;
    }
    visited_with_dir.add(JSON.stringify({ guard_pos, guard_dir }));
  }
};

const create_obstructions = (
  visited: Set<Position>,
  starting_pos: Position,
  starting_dir: number
) => {
  const obs_pos: Position[] = [];
  for (const pos of visited) {
    if (pos.x === starting_pos.x && pos.y === starting_pos.y) {
      continue;
    }

    if (check_loop(pos, starting_pos, starting_dir)) {
      obs_pos.push(pos);
    }
  }

  return obs_pos;
};

const main = () => {
  const visited_pos = get_visited_path();

  if (visited_pos === null) return;
  const { visited, starting_pos, starting_dir } = visited_pos;

  const obs = create_obstructions(visited, starting_pos, starting_dir);
  console.log(obs.length);
};

main();
