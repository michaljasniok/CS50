-- Keep a log of any SQL queries you execute as you solve the mystery.
// sprawdzam jak zbudowana jest baza danych:
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
.schema
// sprawdzam raport sprawy:  3 świadków przesłuchani tego samego dnia wszyscy mówią o piekarni czas kradziezy 10:15 am
SELECT * FROM crime_scene_reports WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
// sprawdzam przesłuchania: odjechał do 10:25 am moze cos byc na kamerach piekarni,  wyciagał kase wczesniej tego dnia z ATM na Leggett Street, uciekajac zadzwonił do kogos rozmowa trwałą nie cała minute.
poleciał najszybszym lotem nastepnego dnia, poprosił wspólnika by kupił owy bilet
SELECT * FROM interviews WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';
// sprawdzam kamery piekarni: potencjalne płyty złodzieji: (5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55)
SELECT * FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25;
// sprawdzam logi z ATM: potencjalne numery kont złodzieji oraz wypłacona kwota:
(28500762 - 48,
28296815 - 20,
76054385 - 60,
49610011 - 50,
16153065 - 80,
25506511 - 20,
81061156 - 30,
26013199 - 35)
SELECT * FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';
// sprawdzam rozmowy telefoniczne: potencjalne numery telefonów złodzieja i wspólnika:
((130) 555-0289 - (996) 555-8899,
(499) 555-9472 - (892) 555-8872,
(367) 555-5533 - (375) 555-8161,
(609) 555-5876 - (389) 555-5198,
(499) 555-9472 - (717) 555-1342,
(286) 555-6063 - (676) 555-6554,
(770) 555-1861 - (725) 555-3243,
(031) 555-6622 - (910) 555-3251,
(826) 555-1652 - (066) 555-9701,
(338) 555-6650 - (704) 555-2131)
SELECT * FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration <= 60;
// łączac uzyskane informacje próbuje uzyskać dane potencjalnych podejrzanych:
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+
SELECT * FROM people WHERE (phone_number = '(130) 555-0289' OR phone_number = '(499) 555-9472' OR phone_number = '(367) 555-5533' OR phone_number = '(609) 555-5876' OR phone_number = '(499) 555-9472' OR phone_number = '(286) 555-6063' OR phone_number = '(770) 555-1861' OR phone_number = '(031) 555-6622' OR phone_number = '(826) 555-1652' OR phone_number = '(338) 555-6650)')
AND (license_plate = '5P2BI95' OR license_plate = '94KL13X' OR license_plate = '6P58WS2' OR license_plate = '4328GD8' OR license_plate = 'G412CB7' OR license_plate = 'L93JTIZ' OR license_plate = '322W7JE' OR license_plate = '0NTHK55');
// aby zawezić liste podejzanych uzywamy dokonanej tranzakcji atm:
+----------------+-----------+---------------+
| account_number | person_id | creation_year |
+----------------+-----------+---------------+
| 49610011       | 686048 Bruce 5773159633  | 2010      |
| 26013199       | 514354 Diana 3592750733  | 2012      |
+----------------+-----------+---------------+
SELECT * FROM bank_accounts WHERE (account_number = 28500762 OR account_number = 28296815 OR account_number = 76054385 OR account_number = 49610011 OR account_number = 16153065 OR account_number = 25506511 OR account_number = 81061156 OR account_number = 26013199)
AND (person_id = 398010 OR person_id = 514354 OR person_id = 560886 OR person_id = 686048);
// sprawdzamy wyloty podejrzanych:
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 18        | 3592750733      | 4C   |
| 24        | 3592750733      | 2C   |
| 36        | 5773159633      | 4A   |
| 54        | 3592750733      | 6C   |
+-----------+-----------------+------+
SELECT * FROM passengers WHERE (passport_number = 5773159633 OR passport_number = 3592750733);
// sprawdzamy czy którys z lotów był odbyty w okresie czasu sugerowanym przez świadka:
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2024 | 7     | 29  | 8    | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+
SELECT * FROM flights WHERE (id = 18 OR id = 24 OR id = 36 OR id = 54) AND year = 2024 AND month = 7 AND day = 29;
// GŁÓWNYM PODEJRZANYM JEST BRUCE
// sprawdzamy jego wspólnika : ROBIN
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
// sprawdzamy gdzie uciekł:
SELECT * FROM airports WHERE id = 4;
