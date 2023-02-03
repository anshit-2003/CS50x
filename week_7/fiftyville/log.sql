-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Query to find the reports of the crime that took place on 28 July 2021 on Humphrey Street
SELECT description
  FROM crime_scene_reports
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND street = 'Humphrey Street';


-- Query to find witnesses and their statements
SELECT name, transcript
  FROM interviews
 WHERE month = 7
   AND year = 2021
   AND day = 28;


-- Query to find people who have the word "bakery in their statements"
SELECT name, transcript
  FROM interviews
 WHERE month = 7
   AND year = 2021
   AND day = 28
   AND transcript LIKE '%bakery%';



-- Query to find the account number of the person who withdrew money from the ATM on Leggett Street
SELECT account_number, amount
  FROM atm_transactions
 WHERE month = 7
   AND year = 2021
   AND day = 28
   AND transaction_type = 'withdraw'
   AND atm_location = 'Leggett Street';


-- Query to find the name of the person who has that account number
SELECT name, atm_transactions.amount
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
  JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
 WHERE atm_transactions.year = 2021
   AND atm_transactions.month = 7
   AND atm_transactions.day = 28
   AND atm_transactions.atm_location = 'Leggett Street'
   AND atm_transactions.transaction_type = 'withdraw';



-- Query to find info of the airport at Fiftyville
SELECT abbreviation, full_name, city
  FROM airports
 WHERE city = 'Fiftyville';



-- Query to find all the flights on July 29 from Fiftyville and ordering them by time
SELECT flights.id, full_name, city, flights.hour, flights.minute
  FROM airports
  JOIN flights
    ON airports.id = flights.destination_airport_id
 WHERE flights.origin_airport_id =(SELECT id FROM airports WHERE city = 'Fiftyville')
   AND flights.month = 7
   AND flights.year = 2021
   AND flights.day = 29
 ORDER BY flights.hour, flights.minute;


-- Query to find passengers who have a flight of 8:20 to LaGuardia
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
  FROM people
  JOIN passengers
    ON people.passport_number = passengers.passport_number
  JOIN flights
    ON passengers.flight_id = flights.id
 WHERE flights.month = 7
   AND flights.year = 2021
   AND flights.day = 29
   AND flights.hour = 8
   AND flights.minute = 20;



-- Query to check the call records of the person who called to find the person who bought the tickets for the thief.
SELECT name, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.caller
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration <= 60
 ORDER BY phone_calls.duration;



-- Query to check the names of the person who recieved those calls
SELECT name, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration <= 60
   ORDER BY phone_calls.duration;


-- Query to check the security logs of the bakery within 10 minutes of the crime and finding their names
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
  FROM people
  JOIN bakery_security_logs
    ON people.license_plate = bakery_security_logs.license_plate
 WHERE bakery_security_logs.year = 2021
   AND bakery_security_logs.month = 7
   AND bakery_security_logs.day = 28
   AND bakery_security_logs.activity = 'exit'
   AND bakery_security_logs.hour = 10
   AND bakery_security_logs.minute >= 15
   AND bakery_security_logs.minute <= 25;


-- Bruce must the thief as he is present in all the 4 lists- List of passengers, list of people who did the specific atm transactions, list of people who called, and list of people who drove away in cars from the bakery.
-- Bruce escaped to New York as he took that flight.
-- Robin must be the accomplice who purchased the flight ticket, and helped Bruce escape to the New York City.