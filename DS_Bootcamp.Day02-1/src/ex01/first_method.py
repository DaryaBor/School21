class Research:
  
    @staticmethod
    def file_reader():
          file='data.csv'
          with open(file) as f:
                return(f.read())


if __name__ == '__main__':
    print(Research.file_reader())