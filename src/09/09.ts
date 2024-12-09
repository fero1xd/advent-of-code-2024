const generate_blocks = (disk_map: string[]): string[] => {
  // "." represents free space
  // 0,1,2... represents file ids
  const blocks = [];
  let file_index = 0;

  for (let i = 0; i < disk_map.length; i++) {
    const is_free_space = i % 2 !== 0;

    for (let j = 0; j < Number(disk_map[i]); j++) {
      if (!is_free_space) {
        blocks.push(`${file_index}`);
      } else {
        blocks.push('.');
      }
    }

    if (!is_free_space) {
      file_index++;
    }
  }

  return blocks;
};

const rearrange_blocks = (blocks: string[]) => {
  for (let i = blocks.length - 1; i >= 0; i--) {
    const f = blocks[i];

    let is_free_space_available = false;

    for (let j = 0; j < i; j++) {
      if (blocks[j] === '.') {
        blocks[j] = f;
        blocks[i] = '.';
        is_free_space_available = true;
        break;
      }
    }

    if (!is_free_space_available) {
      break;
    }
  }
};

const set_free_block = (
  blocks: string[],
  starting: number,
  len: number,
  file: string
) => {
  for (let i = starting; i < starting + len; i++) {
    blocks[i] = file;
  }
};

const rearrange_blocks_p2 = (blocks: string[]) => {
  for (let i = blocks.length - 1; i >= 0; i--) {
    if (isNaN(Number(blocks[i]))) {
      continue;
    }

    let file_length = 0;
    let j = i;
    while (j >= 0 && blocks[j] === blocks[i]) {
      file_length++;
      j--;
    }

    for (let k = 0; k <= j; k++) {
      if (blocks[k] !== '.') continue;

      let dots_len = 0;
      // Look for file_length dots
      for (let x = k; x <= j; x++) {
        if (blocks[x] === '.') dots_len++;
        else break;
      }

      if (dots_len >= file_length) {
        set_free_block(blocks, k, file_length, blocks[i]);
        const st = i - file_length;
        set_free_block(blocks, st + 1, file_length, '.');
        break;
      }
    }

    // Have to +1 coz loop is gonna do the -1
    i = j + 1;
  }
};

const calculate_checksum = (blocks: string[]) => {
  let total = 0;

  for (let i = 0; i < blocks.length; i++) {
    if (blocks[i] === '.') continue;

    total += i * Number(blocks[i]);
  }

  return total;
};

const main = async () => {
  const text = await Deno.readTextFile('./src/09/input.txt');
  const disk_map = text.split('');

  const blocks = generate_blocks(disk_map);
  rearrange_blocks_p2(blocks);

  console.log({ checksum: calculate_checksum(blocks) });
};

main();
