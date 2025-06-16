
def to_dict(countries):
    list_of_tuples = [
    ('Russia', '25'),
    ('France', '132'),
    ('Germany', '132'),
    ('Spain', '178'),
    ('Italy', '162'),
    ('Portugal', '17'),
    ('Finland', '3'),
    ('Hungary', '2'),
    ('The Netherlands', '28'),
    ('The USA', '610'),
    ('The United Kingdom', '95'),
    ('China', '83'),
    ('Iran', '76'),
    ('Turkey', '65'),
    ('Belgium', '34'),
    ('Canada', '28'),
    ('Switzerland', '26'),
    ('Brazil', '25'),
    ('Austria', '14'),
    ('Israel', '12')
    ]
    for country, key in list_of_tuples:
        if  key in countries:
            countries[key].append(country)
        else:
            countries[key] = [country]

    for key in countries:
        values = countries[key]
        for value in values:
            print(f"'{key}' : '{value}'")


if __name__ == '__main__':
    countries = {}
    to_dict(countries)