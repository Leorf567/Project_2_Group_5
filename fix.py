import csv

# Accurate historical GDP mappings for missing values (primarily 2014 values in USD)
gdp_corrections = {
    ("United States", "2014"): "17520000000000.0",
    ("Mexico", "2014"): "1315000000000.0",
    ("Spain", "2014"): "1370000000000.0",
    ("Germany", "2014"): "3890000000000.0",
    ("France", "2014"): "2850000000000.0",
    ("Hong Kong", "2014"): "291000000000.0",
    ("Sweden", "2014"): "580000000000.0",
    ("Saudi Arabia", "2014"): "756000000000.0",
    ("Japan", "2014"): "4850000000000.0",
    ("Italy", "2014"): "2150000000000.0",
    ("India", "2014"): "2039000000000.0",
    ("Russia", "2014"): "2059000000000.0",
    ("Taiwan", "1996"): "290000000000.0",
    ("Taiwan", "2001"): "299000000000.0",
    ("Taiwan", "2014"): "530000000000.0"
}

input_file = "billionaires_flat.txt"
output_file = "billionaires_corrected.txt"

with open(input_file, mode='r', encoding='utf-8') as infile, \
     open(output_file, mode='w', encoding='utf-8', newline='') as outfile:
    
    reader = csv.reader(infile, delimiter='\t')
    writer = csv.writer(outfile, delimiter='\t')
    
    header = next(reader)
    writer.writerow(header)
    
    for row in reader:
        if len(row) == 9:
            year = row[2]
            country = row[7].strip()
            gdp = row[8].strip()
            
            # If GDP is marked as 0.0, replace it with the corrected value if available
            if gdp == "0.0":
                if (country, year) in gdp_corrections:
                    row[8] = gdp_corrections[(country, year)]
                    
        writer.writerow(row)

print("Dataset successfully corrected and saved to billionaires_corrected.txt")