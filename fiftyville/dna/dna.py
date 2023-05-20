import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv)!=3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(0)

    # TODO: Read database file into a variable
    DNAreader=[]
    with open(sys.argv[1]) as file:
        reader=csv.DictReader(file)
        for i in reader:
            DNAreader.append(i)
    # TODO: Read DNA sequence file into a variable
    DNAsequence=""
    with open(sys.argv[2],"r") as file:
        reader=file.readline()
        for i in reader:
            DNAsequence += (i)

    # TODO: Find longest match of each STR in DNA sequence
    L = list(DNAreader[0].keys())
    N = []
    k = 0
    for i in L[1:]:
        N.append(longest_match(DNAsequence,i))
    # TODO: Check database for matching profiles
    for i in DNAreader:
        X=[]
        for j in list(i)[1:]:
            X.append(int(i[j]))
        if(X==N):
            print(i['name'])
            sys.exit(0)
    print("No match")




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
