import sys
import csv


def Main():
    # validate usage of camand line arguments
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sample.txt")
        exit()

    # open csv and text files
    names = open(sys.argv[1], 'r')
    dna = open(sys.argv[2], 'r')

    # read csv file in to dictionary
    reader = csv.DictReader(names)

    # read .txt file to string
    s = dna.readline()

    # declare a dictionary to store strs and their counts
    strcounts = dict()

    # declare a list of strs to search for
    strs = list(reader.fieldnames)

    Counter(s, strs, strcounts)

    print(Result(strcounts, strs, names))


def Counter(s, strs, strcounts):

    lastvalue = "placeholder"
    count = 0
    nextindex = 0

    for i in range(0, len(strs)):
        dnastr = strs[i]

        if dnastr == 'name':
            continue
        else:
            # itterate over characters in string
            for index, c in enumerate(s):

                if index < nextindex and nextindex != 0:
                    continue

                # slice 4 sections of string from character at index
                sect = s[index: index + len(dnastr)]

                # test sample againts the sect
                if sect == dnastr:

                    nextindex = index + len(dnastr)
                    count += 1

                # check for end of consecutive string of sample and update dictionary if necessary
                elif (sect != lastvalue and count > 0):

                    if dnastr in strcounts:
                        if count > strcounts[dnastr]:
                            strcounts[dnastr] = count
                    # if already in dict updae count
                    else:
                        strcounts[dnastr] = count
                    # update count
                    count = 0
                # update last value
                lastvalue = sect
        # if sample not in string at all add to dict with value 0
        if dnastr not in strcounts:
            strcounts[dnastr] = count
        nextindex = 0


def Result(strcounts, strs, names):

    # declare variables
    output = "No Match"
    data = []
    # read data from csv
    for line in names:

        data_line = line.rstrip().split('\t')
        data.append(data_line)

    # itterate over lines in csv
    for l in range(0, len(data)):
        # make string for dict key comparison
        datstr = str(data[l])
        datstr = datstr.strip('[\']')
        lis = datstr.split(',')
        i = 0

        # itterate over values in line
        for i in range(0, len(lis)):
            dnastr = strs[i]

            # get name for return if a match
            if int(i) == 0:
                name = lis[0]
                continue

            # compare counts
            elif int(lis[i]) != int(strcounts[dnastr]) and i < len(lis):
                i = 0
                break
            elif int(lis[i]) == int(strcounts[dnastr]) and i == len(lis) - 1:
                output = name
                break
    # return result
    return(output)


if __name__ == "__main__":
    Main()

