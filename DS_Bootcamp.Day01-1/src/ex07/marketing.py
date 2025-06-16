import sys


def collectoins(text):
    clients = ['andrew@gmail.com', 'jessica@gmail.com', 'ted@mosby.com',
    'john@snow.is', 'bill_gates@live.com', 'mark@facebook.com',
    'elon@paypal.com', 'jessica@gmail.com']
    participants = ['walter@heisenberg.com', 'vasily@mail.ru',
    'pinkman@yo.org', 'jessica@gmail.com', 'elon@paypal.com',
    'pinkman@yo.org', 'mr@robot.gov', 'eleven@yahoo.com']
    recipients = ['andrew@gmail.com', 'jessica@gmail.com', 'john@snow.is']
    clients=set(clients)
    participants=set(participants)
    recipients =set(recipients )
    if text =='call-center':
        print([clients-recipients])
    elif text =='potential_clients':
        print([participants-clients])
    elif text=='loyalty_program':
          print([clients-participants])
    else:
       raise ValueError("Wrong name is given")


if __name__ == '__main__':
    text = str(sys.argv[1])
    collectoins(text)