-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE year=2021 AND month=7 AND day=28;
SELECT * FROM  interviews  WHERE year=2021 AND month=7 AND day=28;
SELECT * FROM  atm_transactions  WHERE year=2021 AND month=7 AND day=28 AND atm_location='Leggett Street';
SELECT * FROM bakery_security_logs  WHERE year=2021 AND month=7 AND day=28 AND activity='exit' AND minute<=10;
SELECT * FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year=2021 AND month=7 AND day=28 AND transaction_type='withdraw' AND atm_location='Leggett Street');
SELECT name FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year=2021 AND month=7 AND day=28 AND transaction_type='withdraw' AND atm_location='Leggett Street'));
SELECT * FROM phone_calls WHERE day=28 AND year=2021 AND month=7 AND duration<=60;
SELECT * FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year=2021 AND month=7 AND day=28 AND transaction_type='withdraw' AND atm_location='Leggett Street')) AND phone_number in (SELECT caller  FROM phone_calls WHERE day=28 AND year=2021 AND month=7 AND duration<=60);
SELECT * FROM people WHERE id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year=2021 AND month=7 AND day=28 AND transaction_type='withdraw' AND atm_location='Leggett Street')) AND phone_number in (SELECT caller  FROM phone_calls WHERE day=28 AND year=2021 AND month=7 AND duration<=60) AND license_plate in (SELECT license_plate FROM bakery_security_logs WHERE year=2021 AND month=7 AND day=28 AND activity='exit');
Select * from passengers where flight_id in (Select id  from flights where year=2021 and month=7 and day=29 and hour=8);
