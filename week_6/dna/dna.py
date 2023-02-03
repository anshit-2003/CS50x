import csv
import sys


def main():

    # TODO: Check for command-line usage
    if (len(sys.argv) != 3):
        print("Provide valid number of command line arguments")
        exit()

    # TODO: Read database file into a variable
    database = open(sys.argv[1], 'r')
    database_csv = csv.DictReader(database)
    dataset = []
    for row in database_csv:
        dataset.append(row)
    database.close()

    # TODO: Read DNA sequence file into a variable
    DNA = open(sys.argv[2], 'r')
    dna_sequence = DNA.read()

    # TODO: Find longest match of each STR in DNA sequence
    subsequences = list(dataset[0].keys())
    subsequences = subsequences[1:]

    results = {}
    for subsequence in subsequences:
        results[subsequence] = longest_match(dna_sequence, subsequence)

    # TODO: Check database for matching profiles
    for person in dataset:
        count = 0
        for subsequence in subsequences:
            if int(person[subsequence]) == results[subsequence]:
                count += 1

        if count == len(subsequences):
            print(person["name"])
            return

    print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
