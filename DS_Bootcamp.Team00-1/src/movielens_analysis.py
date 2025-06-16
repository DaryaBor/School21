import re
import sys
import pytest
from functools import reduce
from collections import Counter
import os
import urllib
import requests
from bs4 import BeautifulSoup
import json
import collections
import functools
import datetime

class statistic:
    @staticmethod
    def average(arr):
        return sum(arr) / len(arr)

    @staticmethod
    def median(arr):
        sorted_arr = sorted(arr)
        l = len(arr)
        return sorted_arr[l // 2] if l % 2 == 1 else (sorted_arr[l // 2 - 1] + sorted_arr[l // 2])/2

    @staticmethod
    def variance(arr):
        mean = statistic.average(arr)
        return sum(map(lambda x: (x-mean)**2, arr)) / len(arr)


class CSVReader:
    @staticmethod
    def _split_and_check_quote(line):
        # если в файле есть запись "...,..." то вся страка становится "..., ""...,..."", ... "
        # важно, что слева и справа ещё добавятся ковычки, и они считываются как символ строки
        # в таком случае меняем "" на " и убираем первую и последнюю ковычку
        if '""' in line:
            line = line[1:-1].replace('""', '"')
        in_quote = False
        lst_line = []
        value = ''
        for i in line:
            if i == '"':
                in_quote = not in_quote
            elif not in_quote and i == ',':
                lst_line.append(value)
                value = ''
            else:
                value += i
        lst_line.append(value)
        return lst_line

    @staticmethod
    def csv_to_list_of_dicts(path_to_the_file, types, set_None=False):
        data = []
        with open(path_to_the_file) as file:
            text = file.read()
            if text[-1] == '\n':
                text = text[:-1]
        lst = text.split('\n')
        header = lst[0].split(',')
        if len(types) != len(header):
            raise ValueError(
                "в types количество элементов не равно количеству столбцов")
        # вставляем None если пуста
        if set_None:
            types = [(lambda f: lambda x: None if x == '' or x == 'None' else f(x))(f)
                     for f in types]

        for line in lst[1:]:
            lst_line = CSVReader._split_and_check_quote(line)
            len_lst_line = len(lst_line)
            data.append({header[i]: types[i](lst_line[i])
                        for i in range(len_lst_line)})

        return data


class Ratings:
    """
    Analyzing data from ratings.csv
    """

    def __init__(self, path_to_the_file):
        """
        Put here any fields that you think you will need.
        """

        self.data = CSVReader.csv_to_list_of_dicts(path_to_the_file,
                                                   [int, int, float, lambda x: datetime.datetime.fromtimestamp(int(x))])

    class Movies:
        def __init__(self, data, path_to_the_file_movies):
            self.ratings = data
            self.movies = CSVReader.csv_to_list_of_dicts(
                path_to_the_file_movies, [int, str, str])

        def dist_by_year(self):
            """
            The method returns a dict where the keys are years and the values are counts. 
            Sort it by years ascendingly. You need to extract years from timestamps.
            """

            return dict(sorted(collections.Counter([line["timestamp"].year for line in self.ratings]).items(), key=lambda x: x[0]))

        # Доп
        def dist_by_month(self):
            """
            The method returns a dict where the keys are month and the values are counts. 
            Sort it by years ascendingly. You need to extract years from timestamps.
            """
            return dict(sorted(collections.Counter([line["timestamp"].month for line in self.ratings]).items(), key=lambda x: x[0]))

        def dist_by_rating(self):
            """
            The method returns a dict where the keys are ratings and the values are counts.
         Sort it by ratings ascendingly.
            """
            return dict(sorted(collections.Counter([line["rating"] for line in self.ratings]).items(), key=lambda x: x[0]))

        def __get_by_movieid(self, movieid, column_name):
            ret = None
            try:
                for line in self.movies:
                    if line["movieId"] == movieid:
                        ret = line[column_name]
            except ValueError:
                raise ValueError(f"неизвестное название столбца {column_name}")
            if ret is None:
                raise IndexError(f"несуществующий movieid = {movieid}")
            return ret

        def top_by_num_of_ratings(self, n):
            """
            The method returns top-n movies by the number of ratings. 
            It is a dict where the keys are movie titles and the values are numbers.
     Sort it by numbers descendingly.
            """
            movieid_count = sorted(collections.Counter([line["movieId"] for line in self.ratings])
                                   .items(), key=lambda x: x[1], reverse=True)
            list_of_tuples = [(self.__get_by_movieid(key, "title"), value)
                              for key, value in movieid_count]
            return dict(list_of_tuples[:n])

        def top_by_ratings(self, n, metric='average'):
            """
            The method returns top-n movies by the average or median of the ratings.
            It is a dict where the keys are movie titles and the values are metric values.
            Sort it by metric descendingly.
            The values should be rounded to 2 decimals.
            """
            if metric == 'average':
                f = statistic.average
            elif metric == 'median':
                f = statistic.median
            elif metric == 'variance':
                f = statistic.variance
            else:
                raise ValueError(
                    "Неизвестное значение аргумента metric. Возможные значения: average, median или variance")
            agg = dict()
            for line in self.ratings:
                agg.setdefault(line['movieId'], []).append(line['rating'])
            agg_f_n_sorted = sorted([(key, round(f(value), 2)) for key, value in agg.items()],
                                    key=lambda x: x[1], reverse=True)[:n]
            return {self.__get_by_movieid(key, 'title'): value for key, value in agg_f_n_sorted}

        def top_controversial(self, n):
            """
            The method returns top-n movies by the variance of the ratings.
            It is a dict where the keys are movie titles and the values are the variances.
          Sort it by variance descendingly.
            The values should be rounded to 2 decimals.
            """
            return self.top_by_ratings(n, metric='variance')

    class Users:
        def __init__(self, data):
            self.ratings = data

        def distribution_by_number(self):
            """returns the distribution of users by the number of ratings made by them."""
            return dict(sorted(collections.Counter([line["userId"] for line in self.ratings])
                               .items(), key=lambda x: x[1], reverse=True))

        def distribution_by_metric(self, metric='average'):
            """returns the distribution of users by average or median ratings made by them."""
            if metric == 'average':
                f = statistic.average
            elif metric == 'median':
                f = statistic.median
            elif metric == 'variance':
                f = statistic.variance
            agg = dict()
            for line in self.ratings:
                agg.setdefault(line['userId'], []).append(line['rating'])
            return dict(sorted([(key, round(f(value), 2)) for key, value in agg.items()],
                               key=lambda x: x[1], reverse=True))

        def top_by_variance(self, n):
            """returns top-n users with the biggest variance of their ratings."""
            return dict(list(self.distribution_by_metric('variance').items())[:n])


class Links:
    """
    Analyzing data from links.csv
    """

    def __init__(self, path_to_the_file, parsed=False):
        """
        Put here any fields that you think you will need.
        """
        self.path_to_the_file = path_to_the_file
        self.headers_for_request = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36",
            "Accept-Language": "en-US,en;q=0.9",
        }
        if parsed:
            self.data = CSVReader.csv_to_list_of_dicts(path_to_the_file,
                                                       [str, str, str, str, str, str, int, int], set_None=True)
        else:
            self.data = CSVReader.csv_to_list_of_dicts(path_to_the_file,
                                                       [str, str, str], set_None=True)

    def __find_value_by_tag(self, tag, soup, string, delete=[], several=False):
        res = soup.find(tag, string=string)
        if res is None:
            return None
        else:
            if several:
                res = "|".join([i.text for i in res.next.next.find_all('a')])
            else:
                res = res.next.next.text
            for i in delete:
                res = res.replace(i, '')
            return res

    # def parse_one_line(self, dict_line):
    def __parse_one_line(self, dict_line):
        print(dict_line["movieId"], end=', ')
        ref = f"https://www.imdb.com/title/tt{dict_line['imdbId']}/"
        r = requests.get(ref, headers=self.headers_for_request)
        if r.status_code == 404:
            ret = None
        else:
            soup = BeautifulSoup(r.text, "html.parser")

            title = soup.find("span", class_="hero__primary-text").text

            runtime = soup.find(
                'div', class_="sc-70a366cc-0").find('ul').find_all('li')[-1].text

            director = self.__find_value_by_tag("span", soup, string='Director')
            # если несколько директоров, то на сайте вместо Director пишут Directors. Иногда он в теге <a>
            # а иногда в span
            if director == None:
                director = self.__find_value_by_tag(
                    "span", soup, string='Directors', several=True)
            if director == None:
                director = self.__find_value_by_tag(
                    "a", soup, string='Directors', several=True)
            if director == None:
                director = self.__find_value_by_tag(
                    "a", soup, string='Director', several=True)

            delete_a = ['$', ',', ' (estimated)', "€", "£", "CA", "A", "NZ", "R", "CN", "NT", "DEM ", "CHF ", "FRF\\xa", 'FRF ', 'ITL ', 'HK', '₹', 
'BEF ', 'RUR ', 'ESP ', 'SEK ', 'FIM ', '¥', '₩', 'ISK\xa0', 'DKK\xa0', 'ATS\xa0', 'NOK\xa0', '₪', 'THB\xa0', 'HUF\xa0'
, 'NLG\xa0', 'BND\xa0', 'THB\xa0', 'PLN\xa0', 'SGD\xa0', 'CZK\xa0']

            gross_worldwide = self.__find_value_by_tag("span",
                                                    soup, string='Gross worldwide', delete=delete_a)

            budget = self.__find_value_by_tag("span",
                                            soup, string='Budget', delete=delete_a)
            ret = f"{dict_line['movieId']},{dict_line['imdbId']},{dict_line['tmdbId']},\"{title}\",\"{runtime}\",\"{director}\",{gross_worldwide},{budget}\n"
        return ret
    
    def parse(self, result_filename):
        "если файл пустой от записываем в него, иначе дописываем спаршенные данные"
        last_id = -1
        if (os.stat(result_filename).st_size == 0):
            with open(result_filename, 'w') as file:
                file.write("movieId,imdbId,tmdbId,title,runtime,director,gross_worldwide,budget\n")
        else:
            links_parsed = Links(result_filename, parsed=True)
            last_id = links_parsed.data[-1]["movieId"]
        for i in self.data:
            if int(i["movieId"]) > int(last_id):
                with open(result_filename, 'a') as file:
                    parsed_line = self.__parse_one_line(i)
                    if parsed_line is not None:
                        file.write(parsed_line)

    def __get_line_by_movieId(self, movieId):
        ret = None
        for line in self.data:
            if line['movieId'] == str(movieId):
                ret = line
                break
        return ret

    def get_imdb(self, list_of_movies, list_of_fields):
        """
The method returns a list of lists [movieId, field1, field2, field3, ...] for the list of movies given as the argument (movieId).
        For example, [movieId, Director, Budget, Cumulative Worldwide Gross, Runtime].
        The values should be parsed from the IMDB webpages of the movies.
     Sort it by movieId descendingly.
        """
        # изменение list_of_fields под файл
        list_of_fields_for_csv = []
        for field in list_of_fields:
            low_field = field.lower()
            if low_field == "cumulative worldwide gross":
                list_of_fields_for_csv.append('gross_worldwide')
            elif field in ['movieId', 'imdbId', 'tmdbId']:
                list_of_fields_for_csv.append(field)
            else:
                list_of_fields_for_csv.append(low_field)
        # проверка на наличие полей
        for field in list_of_fields_for_csv:
            if field not in list(self.data[0].keys()):
                raise ValueError(f"Неизвестное поле {field}")

        imdb_info = []
        for id in list_of_movies:
            line = self.__get_line_by_movieId(id)
            if line is None:
                raise ValueError(f"неизвестный id фильма: {id}")
            imdb_info.append([line[field] for field in list_of_fields_for_csv])
        return imdb_info

    def top_directors(self, n):
        """
        The method returns a dict with top-n directors where the keys are directors and 
        the values are numbers of movies created by them. Sort it by numbers descendingly.
        """
        directors = []
        # print(list(self.data[0].keys()))
        # print(self.data[0]['director'])
        for line in self.data:
            try:
                d = line["director"]
            except:
                print(line)
            if d == None:
                continue
            directors += d.split('|') if '|' in d else [d] 
        return dict(collections.Counter(directors).most_common(n))

    def most_expensive(self, n):
        """
        The method returns a dict with top-n movies where the keys are movie titles and
        the values are their budgets. Sort it by budgets descendingly.
        """
        budgets = {}
        for line in self.data:
            bud = line["budget"] 
            if bud is None:
                continue
            else:
                budgets[line['title']] = bud
        return dict(sorted(budgets.items(), key=lambda x: x[1], reverse=True)[:n])

    def most_profitable(self, n):
        """
        The method returns a dict with top-n movies where the keys are movie titles and
        the values are the difference between cumulative worldwide gross and budget.
     Sort it by the difference descendingly.
        """
        budgets = {}
        for line in self.data:
            bud = line["budget"]
            gww = line["gross_worldwide"]
            if bud is None or gww is None:
                continue
            else:
                budgets[line['title']] = gww - bud
        return dict(sorted(budgets.items(), key=lambda x: x[1], reverse=True)[:n])

    def __runtime_to_minutes(self, r):
        if 'h' not in r:
            hours, minutes = 0, int(r.replace('m', ''))
        elif 'm' not in r:
            hours, minutes = int(r.replace('h', '')), 0
        else:
            hours, minutes = map(int, r.replace('h', '').replace('m', '').split())
        return hours*60+minutes

    def longest(self, n):
        """
        The method returns a dict with top-n movies where the keys are movie titles and
        the values are their runtime. If there are more than one version – choose any.
     Sort it by runtime descendingly.
        """
        longest = []
        for i in self.data:
            r = i['runtime']
            if r in ['TV-PG', 'PG-13']:
                continue
            sum_minutes = self.__runtime_to_minutes(r)
            longest.append((i['title'], r, sum_minutes))
        sorted_longest = sorted(longest, key=lambda x: x[2], reverse=True)
        return dict([(a,b) for a,b,c in sorted_longest][:n])


    def top_cost_per_minute(self, n):
        """
        The method returns a dict with top-n movies where the keys are movie titles and
the values are the budgets divided by their runtime. The budgets can be in different currencies – do not pay attention to it. 
     The values should be rounded to 2 decimals. Sort it by the division descendingly.
        """
        costs = {}
        for line in self.data:
            bud = line["budget"]
            if bud is None:
                continue
            else:
                costs[line['title']] = round(bud / self.__runtime_to_minutes(line['runtime']), 2)
        return dict(sorted(costs.items(), key=lambda x: x[1], reverse=True)[:n])


class TestRatings:
    @pytest.fixture(scope="module")
    def ratings(self):
        return Ratings("data/ratings.csv")

    @pytest.fixture(scope="module")
    def movies(self, ratings):
        return ratings.Movies(ratings.data, "data/movies.csv")

    @pytest.fixture(scope="module")
    def users(self, ratings):
        return ratings.Users(ratings.data)

    def test_init(self, ratings):
        assert type(ratings.data) == list
        assert type(ratings.data[0]) == dict
        assert type(ratings.data[0]["userId"]) == int
        assert type(ratings.data[0]["movieId"]) == int
        assert type(ratings.data[0]["rating"]) == float
        assert type(ratings.data[0]["timestamp"]) == datetime.datetime

    def test_movies_init(self, movies):
        assert type(movies.movies) == list
        assert type(movies.movies[0]) == dict
        assert type(movies.movies[0]["movieId"]) == int
        assert type(movies.movies[0]["title"]) == str
        assert type(movies.movies[0]["genres"]) == str

    def test_dist_by_year(self, movies):
        res = movies.dist_by_year()
        assert type(res) == dict
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == int
        assert type(values[0]) == int
        for i in range(len(keys)-1):
            assert keys[i] < keys[i+1]

    def test_dist_by_month(self, movies):
        res = movies.dist_by_month()
        assert type(res) == dict
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == int
        assert type(values[0]) == int
        for i in range(len(keys)-1):
            assert keys[i] < keys[i+1]

    def test_dist_by_rating(self, movies):
        res = movies.dist_by_rating()
        assert type(res) == dict
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == float
        assert type(values[0]) == int
        for i in range(len(keys)-1):
            assert keys[i] < keys[i+1]

    def test_top_by_num_of_ratings(self, movies):
        res = movies.top_by_num_of_ratings(15)
        assert type(res) == dict
        assert len(res) == 15
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == str
        assert type(values[0]) == int
        for i in range(len(values)-1):
            assert values[i] >= values[i+1]

    def test_top_by_ratings(self, movies):
        # average
        res = movies.top_by_ratings(1000)
        assert type(res) == dict
        assert len(res) == 1000
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == str
        assert type(values[0]) == float
        for i in range(len(values)-1):
            assert values[i] >= values[i+1]
        # median
        res = movies.top_by_ratings(1000, 'median')
        assert type(res) == dict
        assert len(res) == 1000
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == str
        assert type(values[0]) == float
        for i in range(len(values)-1):
            assert values[i] >= values[i+1]

    def top_controversial(self, movies):
        res = movies.top_controversial(1000)
        assert type(res) == dict
        assert len(res) == 1000
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == str
        assert type(values[0]) == float
        for i in range(len(values)-1):
            assert values[i] >= values[i+1]

    def test_distribution_by_number(self, users):
        res = users.distribution_by_number()
        assert type(res) == dict
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == int
        assert type(values[0]) == int
        for i in range(len(values)-1):
            assert values[i] >= values[i+1]

    def test_distribution_by_metric(self, users):
        res = users.distribution_by_metric('average')
        assert type(res) == dict
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == int
        assert type(values[0]) == float
        for i in range(len(values)-1):
            assert values[i] >= values[i+1]
        res = users.distribution_by_metric('median')
        assert type(res) == dict
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == int
        assert type(values[0]) == float
        for i in range(len(values)-1):
            assert values[i] >= values[i+1]

    def test_top_by_variance(self, users):
        res = users.top_by_variance(200)
        assert type(res) == dict
        assert len(res) == 200
        keys = list(res.keys())
        values = list(res.values())
        assert type(keys[0]) == int
        assert type(values[0]) == float
        for i in range(len(values)-1):
            assert values[i] >= values[i+1] 

class Movies:
    """
    Analyzing data from movies.csv
    """
    def __init__(self, path_to_the_file):
        self.file = path_to_the_file
        with open (self.file, encoding='utf-8') as f:
            self.text= f.readlines()
        
    def dist_by_release(self):
        """
        The method returns a dict or an OrderedDict where the keys are years and the values are counts. 
        You need to extract years from the titles. Sort it by counts descendingly.
        """
        release_years={}
        for t in self.text:
            year=re.search(r"\((\d{4})\)",t)
            if year:
                if year.group(1) in release_years:
                    release_years[year.group(1)]+=1
                else:
                    release_years[year.group(1)]=1
        release_years =dict(sorted(release_years.items(), key=lambda x: x[1], reverse=True))
        return release_years
    
    def dist_by_genres(self):
        """
        The method returns a dict where the keys are genres and the values are counts.
        Sort it by counts descendingly.
        """
        genres={}
        for t in self.text:
            gens = t[t.rfind(","):]
            matches_genres=re.findall(r"(\(|\|)([^(|)]*)(\)|\|)", gens)
            cleaned_matches = [value[1].strip() for value in matches_genres]
            for genre in cleaned_matches:
                if genre in genres:
                    genres[genre]+=1
                else:
                    genres[genre]=1
        genres =dict(sorted(genres.items(), key=lambda x: x[1], reverse=True))
        return genres
        
    def most_genres(self, n):
        """
        The method returns a dict with top-n movies where the keys are movie titles and 
        the values are the number of genres of the movie. Sort it by numbers descendingly.
        """
        movies={}
        for t in self.text:
            matches_name=re.findall(r",\s*(.*?)\s+\(", t)
            matches_genres=re.findall(r"[^\W\d_]+", t[t.rfind(","):])
            for name in matches_name:
                if 'no' and 'genres' and 'listed' in matches_genres:
                    movies[name]=0
                else:
                    movies[name]=len(matches_genres)     
        movies=dict(sorted(movies.items(), key=lambda x: x[1], reverse=True))  
        movies = dict(list(movies.items())[1:int(n)]) 
        return movies
    
    def movies_by_year(self, year):
        """
        The method returns a list of movies by the year
        """
        movies=[]
        for t in self.text[1:]:
            get_year=re.search(r"\((\d{4})\)",t)
            if get_year and int(year)==int(get_year.group(1)):
                movies.append(re.search(r'(?<=,)[^\(]+',t).group(0)[:-1])
        if len(movies)==0:
            print("Don't have movies by this year")
        return movies


class Tags:
    """
    Analyzing data from tags.csv
    """
    def __init__(self, path_to_the_file):
        self.file = path_to_the_file
        self.unique_tags=[]
        with open (self.file, encoding='utf-8') as f:
            self.text= f.readlines()
        self.tags=[]
        for t in self.text:
            tgs = re.findall(r'[^,]+', t)
            self.tags.append(tgs[2])
      

    def most_words(self, n):
        """
        The method returns top-n tags with most words inside. It is a dict 
        where the keys are tags and the values are the number of words inside the tag.
        Drop the duplicates. Sort it by numbers descendingly.
        """
        big_tags ={}
        for t in self.text:
            tgs = re.findall(r'[^,]+', t)
            signs = re.findall(r'([^a-zA-Z0-9])\1+',tgs[2])
            if signs and signs[0] not in big_tags :
                big_tags[signs[0]]=0
            elif tgs[2].lower() not in big_tags:
                big_tags[tgs[2]]=len(tgs[2].split())
        big_tags=dict(sorted(big_tags.items(), key=lambda x: x[1], reverse=True))  
        big_tags = dict(list(big_tags.items())[1:int(n)])
        return big_tags

    # def longest(self, n):
    #     big_tags={}
    #     for t in self.text:
    #         tgs = re.findall(r'[^,]+', t)
    #         if tgs[2].lower() not in big_tags:
    #             big_tags[tgs[2]]=len(tgs[2])
    #     big_tags=dict(sorted(big_tags.items(), key=lambda x: x[1], reverse=True))
    #     big_tags = list(big_tags.keys())[1:int(n)]
    #     return big_tags
    def longest(self, n):
        """
        The method returns top-n longest tags in terms of the number of characters.
        It is a list of the tags. Drop the duplicates. Sort it by numbers descendingly.
        """
        return sorted(list(set([re.findall(r'[^,]+', t)[2] for t in self.text])), key=lambda x: len(x), reverse=True)[1:int(n)]

    def most_words_and_longest(self, n):
        """
        The method returns the intersection between top-n tags with most words inside and 
        top-n longest tags in terms of the number of characters.
        Drop the duplicates. It is a list of the tags.
        """
        longest_big_tags = self.longest(n)
        most_big_tags=self.most_words(n)
        big_tags = list(set(longest_big_tags) & set(most_big_tags.keys()))
        return big_tags
        
    def most_popular(self, n):
        """
        The method returns the most popular tags. 
        It is a dict where the keys are tags and the values are the counts.
        Drop the duplicates. Sort it by counts descendingly.
        """
        popular_tags=dict(Counter(self.tags))
        popular_tags=dict(sorted(popular_tags.items(), key=lambda x: x[1], reverse=True))  
        popular_tags = dict(list(popular_tags.items())[:int(10)])
        return popular_tags
        
    def tags_with(self, word):
        """
        The method returns all unique tags that include the word given as the argument.
        Drop the duplicates. It is a list of the tags. Sort it by tag names alphabetically.
        """
        self.unique_tags=list(set(self.tags)) 
        tags_with_word=[]
        for wrd in self.unique_tags:
            if word.lower() in wrd.lower().split():
                tags_with_word.append(wrd)
        tags_with_word = sorted(tags_with_word)
        return tags_with_word 

class TestTags:

    @pytest.fixture
    def tags_obj(self):
        path = "../src/data/tags.csv"
        return Tags(path)

    def test_most_words(self,tags_obj):
        n=5
        assert type(tags_obj.most_words(n))==dict
        assert type(tags_obj.most_words(n)['villain nonexistent or not needed for good story'])==int
        for t in range(1,len(tags_obj.most_words(n))):
           assert list(tags_obj.most_words(n).values())[t]<=list(tags_obj.most_words(n).values())[t-1]
                
    def test_longest(self, tags_obj):
        n=5
        assert type(tags_obj.longest(n))==list
        for t in range(1,len(tags_obj.longest(n))):
           assert len(tags_obj.longest(n)[t])<=len(tags_obj.longest(n)[t-1])

    def test_most_words_and_longest(self,tags_obj):
        n=5
        assert type(tags_obj.most_words_and_longest(n))==list
        assert type(tags_obj.most_words_and_longest(n)[0])==str
        
    def test_most_popular(self, tags_obj):
        n=5
        assert type(tags_obj.most_popular(n))==dict
        assert type(tags_obj.most_popular(n)['sci-fi'])==int
        for t in range(1,len(tags_obj.most_popular(n))):
           assert list(tags_obj.most_popular(n).values())[t]<=list(tags_obj.most_popular(n).values())[t-1]

    def test_tags_with(self, tags_obj):
        word="Alan"
        assert type(tags_obj.tags_with(word))==list
        assert type(tags_obj.tags_with(word)[0])==str

class TestMovies:

    @pytest.fixture
    def movies_obj(self):
        path = "../src/data/movies.csv"
        return Movies(path)

    def test_dist_by_release(self,movies_obj):

        assert type(movies_obj.dist_by_release())==dict
        assert type(movies_obj.dist_by_release()['2010'])==int
        for t in range(1,len(movies_obj.dist_by_release())):
           assert list(movies_obj.dist_by_release().values())[t]<=list(movies_obj.dist_by_release().values())[t-1]
                
    def test_dist_by_genres(self, movies_obj):
        assert type(movies_obj.dist_by_genres())==dict
        assert type(movies_obj.dist_by_genres()['Sci-Fi'])==int
        for t in range(1,len(movies_obj.dist_by_genres())):
           assert list(movies_obj.dist_by_genres().values())[t]<=list(movies_obj.dist_by_genres().values())[t-1]

    def test_most_genres(self,movies_obj):
        n=5
        assert type(movies_obj.most_genres(n))==dict
        assert type(movies_obj.most_genres(n)['Patlabor: The Movie'])==int
        for t in range(1,len(movies_obj.most_genres(n))):
           assert list(movies_obj.most_genres(n).values())[t]<=list(movies_obj.most_genres(n).values())[t-1]
    
    def test_movies_by_year(self,movies_obj):
        year=1995
        assert type(movies_obj.movies_by_year(year))==list
        assert type(movies_obj.movies_by_year(year)[0])==str

class TestLinks:
    @pytest.fixture(scope="module")
    def links(self):
        return Links("data/links.csv")
    
    @pytest.fixture(scope="module")
    def links_parsed(self):
        return Links("data/links_parsed.csv", parsed=True)

    def test_init(self, links):
        assert type(links.data) == list
        assert type(links.data[0]) == dict
        assert type(links.data[0]["movieId"]) == str
        assert type(links.data[0]["imdbId"]) == str
        assert type(links.data[0]["tmdbId"]) == str

    def test_init_parced(self, links_parsed):
        assert type(links_parsed.data) == list
        assert type(links_parsed.data[0]) == dict
        assert type(links_parsed.data[0]["movieId"]) == str
        assert type(links_parsed.data[0]["imdbId"]) == str
        assert type(links_parsed.data[0]["tmdbId"]) == str
        assert type(links_parsed.data[0]["title"]) == str
        assert type(links_parsed.data[0]["runtime"]) == str
        assert type(links_parsed.data[0]["director"]) == str
        assert type(links_parsed.data[0]["gross_worldwide"]) == int
        assert type(links_parsed.data[0]["budget"]) == int
    
    def test_get_imdb(self, links_parsed):
        res = links_parsed.get_imdb([1, 2, 3, 106], ['movieId', 'Director', 'Budget', 'Cumulative Worldwide Gross', 'Runtime'])
        assert type(res) == list
        assert type(res[0]) == list
        assert len(res) == 4
        types = [str, str, int, int, str]
        for i in range(len(res[0])):
            assert type(res[0][i]) == types[i]
    def test_top_directors(self, links_parsed):
        res = links_parsed.top_directors(100)
        assert type(res) == dict
        assert type(list(res.keys())[0]) == str
        assert type(list(res.values())[0]) == int
        items = list(res.items())
        for i in range(len(items)-1):
            assert items[i][1] >= items[i+1][1] 
    def test_most_expensive(self, links_parsed):
        res = links_parsed.most_expensive(100)
        assert type(res) == dict
        assert type(list(res.keys())[0]) == str
        assert type(list(res.values())[0]) == int
        items = list(res.items())
        for i in range(len(items)-1):
            assert items[i][1] >= items[i+1][1] 
    def test_most_profitable(self, links_parsed):
        res = links_parsed.most_profitable(100)
        assert type(res) == dict
        assert type(list(res.keys())[0]) == str
        assert type(list(res.values())[0]) == int
        items = list(res.items())
        for i in range(len(items)-1):
            assert items[i][1] >= items[i+1][1] 
    def test_longest(self, links_parsed):
        res = links_parsed.longest(100)
        assert type(res) == dict
        assert type(list(res.keys())[0]) == str
        assert type(list(res.values())[0]) == str
    def test_top_cost_per_minute(self, links_parsed):
        res = links_parsed.top_cost_per_minute(100)
        assert type(res) == dict
        assert type(list(res.keys())[0]) == str
        assert type(list(res.values())[0]) == float
        items = list(res.items())
        for i in range(len(items)-1):
            assert items[i][1] >= items[i+1][1]