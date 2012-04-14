CREATE TABLE tests (id integer primary key autoincrement, name text, description text);
CREATE TABLE tickets (id integer primary key autoincrement, name text);
CREATE TABLE tickets_in_tests (ticket_id integer, test_id integer);
CREATE TABLE questions_simple (id integer primary key  autoincrement, question text, answer1 text, answer2 text, answer3 text, answer4 text, answer5 text, correct integer);
CREATE TABLE questions_in_tickets (question_id integer, ticket_id integer);
/*CREATE TABLE questions ();
CREATE TABLE answers (id integer, answer text);
CREATE TABLE answers_in_questions (answer_id integer, question_id integer);
CREATE TABLE test_log (id integer primary key autoincrement, start_time text, duration integer);*/
CREATE TABLE answer_log (testee_id integer, timestamp text, question_id integer, answer_id integer);
CREATE TABLE testees (id integer primary key autoincrement, name text, position text, company text, timestamp text, test_id integer, ticket_id integer);

CREATE TRIGGER testee_timestamp AFTER  INSERT ON testees
BEGIN
UPDATE testees SET timestamp = DATETIME('NOW')
         WHERE rowid = new.rowid;
END;

CREATE TRIGGER log_timestamp AFTER  INSERT ON answer_log
BEGIN
UPDATE answer_log SET timestamp = DATETIME('NOW')
         WHERE rowid = new.rowid;
END;
