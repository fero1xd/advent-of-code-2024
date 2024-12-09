const generate_blocks = (disk_map: string[]): string[] => {
  // "." represents free space
  // 0,1,2... represents file ids
  const blocks = [];
  let file_index = 0;

  for (let i = 0; i < disk_map.length; i++) {
    const is_free_space = Number(disk_map[i]) % 2 === 0;

    for (let j = 0; j < Number(disk_map[i]); j++) {
      if (!is_free_space) {
        blocks.push(`${file_index}`);
      } else {
        blocks.push('.');
      }
    }

    !is_free_space && file_index++;
  }

  console.log(file_index);

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

const main = async () => {
  const text = await Deno.readTextFile('./src/09/sample.txt');
  const disk_map = text.split('');

  const blocks = generate_blocks(disk_map);

  console.log({ before: blocks });
  rearrange_blocks(blocks);
  console.log(blocks);
};

main();
