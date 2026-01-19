import csv
import sys


def main():

    # TODO: Check for command-line usage
    if (len(sys.argv)) == 3:
        csv_file = sys.argv[1]
        dna_file = sys.argv[2]
    else:
        sys.exit(print("Invalid number of CMA"))
    # TODO: Read database file into a variable
    with open(csv_file, 'r') as file1:
        reader1 = csv.DictReader(file1)
        database = list(reader1)
        str_names = reader1.fieldnames[1:]
    # TODO: Read DNA sequence file into a variable
    with open(dna_file, 'r') as file2:
        dna_sec = file2.read()
    # TODO: Find longest match of each STR in DNA sequence
    dna_counts = {}
    for STR in str_names:
        dna_counts[STR] = str(longest_match(dna_sec, STR))
    # TODO: Check database for matching profiles
    for row in database:
        if all(row[STR] == dna_counts[STR] for STR in str_names):
            return print(row["name"])
    return print("No match")
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
