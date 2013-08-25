# coding=utf-8

# Скрипт для уравнивания количества вопросо в билетах

import sqlite3

def main():
    print "Please check customdb.db file to be present in current directory"

    conn = sqlite3.connect("customdb.db")
    conn.text_factory = str
    c = conn.cursor()
    for row in c.execute('SELECT id FROM tickets'):
        # Определить количество вопросов в билете

        c2 = conn.cursor()
        c2.execute('SELECT count(1) FROM questions_in_tickets WHERE ticket_id = ?', (row[0],))

        count = c2.fetchone()[0]

        for i in range(10-count):
            values = ('вопрос %d' % i, 'ответ1', 'ответ2', 'ответ3', 'ответ4', 'ответ5', 1 )
            c2.execute('INSERT INTO questions_simple (question, answer1, answer2, answer3, answer4, answer5, correct) VALUES (?,?,?,?,?,?,?)', values)
            question_id = c2.lastrowid

            c2.execute('INSERT INTO questions_in_tickets (question_id, ticket_id) VALUES (?,?)', (question_id, row[0]))
            conn.commit()

        print "Process for id %d finished" % row[0]

if __name__ == "__main__":
    main()
