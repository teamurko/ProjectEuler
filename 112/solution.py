
def main():
    percentage = 99
    def is_bouncy(sequence):
        consequtive_digits_pairs = list(zip(sequence, sequence[1:]))
        return (any(x > y for x, y in consequtive_digits_pairs) and
                any(x < y for x, y in consequtive_digits_pairs))
    numbers_count = 1
    bouncy_numbers_count = 0
    while (bouncy_numbers_count * 100 < numbers_count * percentage):
        numbers_count += 1
        if is_bouncy(str(numbers_count)):
            bouncy_numbers_count += 1
    print(numbers_count)


if __name__ == "__main__":
    main()
