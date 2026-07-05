import billionaires
import csv

data = billionaires.get_billionaire()

with open('billionaires_flat.txt', 'w', newline='', encoding='utf-8') as f:
    writer = csv.writer(f, delimiter='\t') 
    
    writer.writerow(['Name', 'Rank', 'Year', 'Company', 'Sector', 'Age', 'Net_Worth_Billions'])
    
    for b in data:
        writer.writerow([
            b['name'],
            b['rank'],
            b['year'],
            b['company']['name'],
            b['company']['sector'],
            b['demographics']['age'],
            b['wealth']['worth in billions']
        ])

print("Successfully exported to billionaires_flat.txt!")