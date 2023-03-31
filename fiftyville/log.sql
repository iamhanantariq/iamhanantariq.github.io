-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports WHERE month=7 AND day=28;
-- Mentions 1015am theft and bakery, ID = 295

SELECT * FROM interviews where transcript LIKE "%bakery%";
-- ID 161 - got in a car to escape at that time (1015..)
-- ID 162 - ATM at leggett street withdrawing money before robery
-- ID 163 - called someone for <1min - planning to take earlist flight out of fiftyville tomorrow (7/29/2021),
-- asked someone else to buy ticket (accomplice)

select * from bakery_security_logs where month=7 and day=28 and hour >= 10 and activity = "exit";
--ID 260-268 are all cars that left and their licence plates (1016 - 1035am)

select * from atm_transactions where month=7 and day=28 and atm_location like "leggett street" and transaction_type like "withdraw";
-- Provides 8 account numbers that took out some money

-- To get person IDs from transactions
select person_id from bank_accounts where account_number in (select account_number from atm_transactions where month=7 and day=28 and atm_location like "leggett street" and transaction_type like "withdraw");

select * from phone_calls where month=7 and day=28 and duration < 61;
-- Provides phone numbers and calls < 60sec

-- Gets people based on ATM withdrawl at legget street
select * from people where id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where month=7 and day=28 and atm_location like "leggett street" and transaction_type like "withdraw"));

-- 4 people that left after 1015-1026 theft and withdrawl at legget st, need to cross reference with flights
select * from bakery_security_logs where license_plate in (select license_plate from people where id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where month=7 and day=28 and atm_location like "leggett street" and transaction_type like "withdraw"))) and month=7 and day=28 and activity = "exit" and minute <27;

select * from flights where month=7 and day=29;

select * from airports where id in (select destination_airport_id from flights where month=7 and day=29);

select * from passengers where flight_id in (select id from flights where month=7 and day=29);

-- Get passport from licence plate of 4 suspects
select passport_number from people where license_plate in (select license_plate from bakery_security_logs where license_plate in (select license_plate from people where id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where month=7 and day=28 and atm_location like "leggett street" and transaction_type like "withdraw"))) and month=7 and day=28 and activity = "exit" and minute < 27);

select passport_number from passengers where flight_id in (select id from flights where month=7 and day=29) and passport_number in (select passport_number from people where license_plate in (select license_plate from bakery_security_logs where license_plate in (select license_plate from people where id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where month=7 and day=28 and atm_location like "leggett street" and transaction_type like "withdraw"))) and month=7 and day=28 and activity = "exit" and minute <27));

-- Test for caller and reciever, caller = diana 359pass (boston - Philip) and bruce 577pass (nyc - robin)
-- cross checked phone numbers
-- receiver = luca 849pass
select * from people where passport_number in (select passport_number from passengers where flight_id in (select id from flights where month=7 and day=29) and passport_number in (select passport_number from people where license_plate in (select license_plate from bakery_security_logs where license_plate in (select license_plate from people where id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where month=7 and day=28 and atm_location like "leggett street" and transaction_type like "withdraw"))) and month=7 and day=28 and activity = "exit" and minute <26))) and phone_number in (select receiver from phone_calls where month=7 and day=28 and duration < 61);

-- Check their flights to be the same one
-- luca on 36 flight Id and same with Bruce, but luca no match
select * from passengers where flight_id in (select id from flights where month=7 and day=29) and passport_number in (select passport_number from people where passport_number in (select passport_number from passengers where flight_id in (select id from flights where month=7 and day=29) and passport_number in (select passport_number from people where license_plate in (select license_plate from bakery_security_logs where license_plate in (select license_plate from people where id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where month=7 and day=28 and atm_location like "leggett street" and transaction_type like "withdraw"))) and month=7 and day=28 and activity = "exit" and minute <26))) and phone_number in (select receiver from phone_calls where month=7 and day=28 and duration < 61));

select * from people where phone_number in (select receiver from phone_calls where month=7 and day=28 and duration < 61);

--phone number not used i think
-- 389 luca with 609