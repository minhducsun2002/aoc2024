def read() -> list[str]:
    arr = []
    with open("./input.txt") as f:
        data = f.read()
        block = True
        current = 0
        for c in data:
            if block:
                for i in range(0, int(c)):
                    arr.append(str(current))
                current += 1
            else:
                for i in range(0, int(c)):
                    arr.append('.')
            block = not block
    return arr

def find_next(arr: list[str], starting: int) -> int:
    for idx in range(starting, len(arr)):
        if arr[idx] == '.':
            return idx
    return -1
def solve1() -> int:
    arr = read()
    next_position = 0
    for last in reversed(range(0, len(arr))):
        next_position = find_next(arr, next_position)
        if next_position == -1:
            break
        if next_position > last:
            break

        arr[next_position] = arr[last]
        arr[last] = '.'

    output = 0
    for i in range(0, len(arr)):
        if arr[i] == '.':
            continue
        output += int(arr[i]) * i

    return output

def list_files(l: list[str]) -> list[(int, int, str)]: # idx, count, id
    now = l[0]
    count = 0
    start = 0
    out = []
    for idx in range(1, len(l)):
        curr = l[idx]
        if curr == '.':
            continue
        if curr == now:
            count += 1
        else:
            out.append((start, count, now))

            count = 1
            now = curr
            start = idx

    out.append((start, count, now))

    return out
def list_spaces(l: list[str]) -> list[(int, int)]: # start, length
    out = []

    counter = 0
    start = -1
    for idx in range(0, len(l)):
        if l[idx] == '.':
            counter += 1
            if start == -1:
                start = idx
        else:
            if start != -1:
                out.append((start, counter))
                counter = 0
                start = -1

    if start != -1:
        out.append((start, counter))

    return out

def find_next_fitting_space(pieces: list[(int, int)], size: int) -> int:
    for idx in range(0, len(pieces)):
        start, length = pieces[idx]
        if length >= size:
            return idx
    return -1

def assign_space_to_file(arr: list[str], sp: list[(int, int)], space_index: int, file: (int, int, int)) -> list[(int, int)]:
    start, length, file_id = file
    next_position, space_size = sp[space_index]

    move_file_to_slot(arr, file, sp[space_index])

    # calculate new slot
    remaining = space_size - length

    before = sp[0:space_index]
    after = sp[space_index + 1:]

    if remaining == 0:
        return before + after
    else:
        return before + [(next_position + length, space_size - length)] + after
def move_file_to_slot(arr: list[str], file: (int, int, int), target_space: (int, int)):
    next_position, space_size = target_space
    start, length, file_id = file
    for pos in range(next_position, next_position + length):
        arr[pos] = file_id

        diff = pos - next_position
        arr[start + diff] = '.'

def solve2() -> int:
    arr = read()
    files = list_files(arr)
    spaces = list_spaces(arr)

    for file in reversed(files):
        start, length, file_id = file
        fitting_index = find_next_fitting_space(spaces, length)
        if fitting_index == -1:
            continue
        next_position, space_size = spaces[fitting_index]
        if next_position > start:
            continue
        spaces = assign_space_to_file(arr, spaces,  fitting_index, file)

    output = 0
    for i, item in enumerate(arr):
        output += 0 if item.startswith('.') else int(item) * i

    return output

print(solve1())
print(solve2())