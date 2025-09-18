-- TASK 1
-- Q1

-- BEFORE
SELECT * FROM Stall_items WHERE Stall_ID='S1' AND Item_name='Mushroom Risotto';

-- COMMAND
DELIMITER $$
CREATE TRIGGER trg_after_purchased_decrease_stock
AFTER INSERT ON Purchased
FOR EACH ROW
BEGIN
    UPDATE Stall_items
    SET Total_quantity = Total_quantity - NEW.Quantity
    WHERE Stall_ID = NEW.Stall_ID
      AND Item_name = NEW.Item_name;
END$$
DELIMITER ;

-- AFTER
INSERT INTO Purchased (SRN, Stall_ID, Item_name, Timestamp, Quantity)
VALUES ('P1017', 'S1', 'Mushroom Risotto', NOW(), 2);
SELECT * FROM Stall_items WHERE Stall_ID='S1' AND Item_name='Mushroom Risotto';

-- Q2

-- BEFORE 
DESC Purchased;
SELECT * FROM Purchased;

-- COMMAND
DELIMITER $$
CREATE TRIGGER trg_before_purchased_check
BEFORE INSERT ON Purchased
FOR EACH ROW
BEGIN
IF NEW.Quantity > 5 THEN
SIGNAL SQLSTATE '45000'
SET MESSAGE_TEXT = 'Cannot purchase more than 5 units in a single transaction.';
END IF;
END$$
DELIMITER ;

-- AFTER
INSERT INTO Purchased (SRN, Stall_ID, Item_name, Timestamp, Quantity)
VALUES ('P1017', 'S1', 'Mushroom Risotto', NOW(), 6);

INSERT INTO Purchased (SRN, Stall_ID, Item_name, Timestamp, Quantity)
VALUES ('P1017', 'S1', 'Mushroom Risotto', NOW(), 3);



-- TASK 2

-- Q1

-- BEFORE
SELECT * FROM Purchased WHERE Stall_ID='S1';
SELECT * FROM Stall_items WHERE Stall_ID='S1';

-- COMMAND
DELIMITER $$
CREATE PROCEDURE GetStallSales(
IN in_stall_id VARCHAR(10)
)
BEGIN
DECLARE total_revenue DECIMAL(12,2);
SELECT SUM(si.Price_per_unit * p.Quantity)
INTO total_revenue
FROM Purchased p
JOIN Stall_items si
ON p.Stall_ID = si.Stall_ID
AND p.Item_name = si.Item_name
WHERE p.Stall_ID = in_stall_id;
SET total_revenue = COALESCE(total_revenue, 0.00);
SELECT total_revenue AS StallRevenue;
END$$
DELIMITER ;

-- AFTER
CALL GetStallSales('S1');

-- Q2

-- BEFORE
SELECT * FROM Registration WHERE Event_ID='E2';

-- COMMAND

DROP PROCEDURE IF EXISTS RegisterParticipant;

DELIMITER $$
CREATE PROCEDURE RegisterParticipant(
IN in_event_id VARCHAR(10),
IN in_srn VARCHAR(20),
IN in_registration_id INT
)
BEGIN
INSERT INTO Registration (RegistrationID, Event_ID, SRN)
VALUES (in_registration_id, in_event_id, in_srn);
END$$
DELIMITER ;


-- AFTER
CALL RegisterParticipant('E2', 'P1017', 9001);
SELECT * FROM Registration WHERE Event_ID='E2';




-- TASK 3

-- Q1

-- BEFORE
SELECT * FROM Event WHERE Event_ID='E2';


-- COMMAND

DROP FUNCTION IF EXISTS GetEventCost;

DELIMITER $$
CREATE FUNCTION GetEventCost(in_event_id VARCHAR(10))
RETURNS DECIMAL(8,2)
DETERMINISTIC
READS SQL DATA
BEGIN
DECLARE v_price DECIMAL(8,2);
SELECT Price
INTO v_price
FROM Event
WHERE Event_ID = in_event_id
LIMIT 1;
RETURN COALESCE(v_price, 0.00);
END$$
DELIMITER ;


-- AFTER
SELECT GetEventCost('E2') AS EventPrice;


-- Q2

-- BEFORE
SELECT * FROM Purchased WHERE SRN='P1017';
SELECT * FROM Stall_items;


-- COMMAND

DROP FUNCTION IF EXISTS GetParticipantPurchaseTotal;

DELIMITER $$
CREATE FUNCTION GetParticipantPurchaseTotal(in_srn VARCHAR(20))
RETURNS DECIMAL(12,2)
DETERMINISTIC
READS SQL DATA
BEGIN
DECLARE v_total DECIMAL(12,2);
SELECT SUM(si.Price_per_unit * p.Quantity)
INTO v_total
FROM Purchased p
JOIN Stall_items si
ON p.Stall_ID = si.Stall_ID
AND p.Item_name = si.Item_name
WHERE p.SRN = in_srn;
RETURN COALESCE(v_total, 0.00);
END$$
DELIMITER ;

-- AFTER
SELECT GetParticipantPurchaseTotal('P1017') AS TotalSpent;

