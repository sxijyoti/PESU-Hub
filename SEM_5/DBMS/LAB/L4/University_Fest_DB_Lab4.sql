USE University_Fest;

-- TASK 1

-- Q1
-- Before
SELECT * FROM Event;
-- Command
INSERT INTO Event (Event_ID, Event_name, Building, Floor, Room_no, Price, TeamID)
VALUES ('E2','AI Hackathon','Seminar Hall','2','205',900,'T4');
-- After
SELECT * FROM Event;

-- Q2
-- Before
SELECT * FROM Stall_items;
-- Command
UPDATE Stall_items
SET Total_quantity = 25
WHERE Stall_ID='S1' AND Item_name='Mushroom Risotto';
-- After
SELECT * FROM Stall_items;

-- Q3
-- Before
SELECT * FROM Registration;
-- Command
DELETE FROM Registration
WHERE Event_ID='E1' AND SRN LIKE 'P100%';
-- After
SELECT * FROM Registration;

-- Q4
-- Before
SELECT * FROM Purchased;
-- Command
INSERT INTO Purchased (SRN, Stall_ID, Item_name, Timestamp, Quantity)
VALUES ('P1017','S6','Fish Tacos','2025-07-10 14:00:00',3);
-- After
SELECT * FROM Purchased;


-- TASK 2

-- Q5
-- Before
SELECT * FROM Registration;
-- Command & After
SELECT SRN FROM (
    SELECT SRN FROM Registration WHERE Event_ID='E2' AND SRN NOT IN 
        (SELECT SRN FROM Registration WHERE Event_ID='E5')
    UNION
    SELECT SRN FROM Registration WHERE Event_ID='E5' AND SRN NOT IN 
        (SELECT SRN FROM Registration WHERE Event_ID='E2')
) AS OnlyE2orE5;

-- Q6
-- Before
SELECT * FROM Participants;
SELECT * FROM Visitors;
-- Command & After
SELECT p.SRN, p.Name AS Participant_Name,
       v.Name AS Visitor_Name,
       COUNT(v.Name) OVER (PARTITION BY p.SRN) AS Visitor_Count
FROM Participants p
LEFT JOIN Visitors v ON p.SRN = v.SRN;

-- Q7
-- Before
SELECT * FROM Registration;
-- Command & After
SELECT e.Event_ID, e.Event_name
FROM Event e
JOIN Registration r ON e.Event_ID = r.Event_ID
JOIN Participants p ON r.SRN = p.SRN
GROUP BY e.Event_ID, e.Event_name
HAVING SUM(p.Gender='M') = SUM(p.Gender='F');

-- Q8
-- Before
SELECT * FROM Event;
SELECT * FROM Teams;
SELECT * FROM Fest;
-- Command & After
SELECT e.Event_name,
CASE WHEN f.Year > 2047 THEN 1 ELSE 0 END AS After_Golden_Jubilee
FROM Event e
JOIN Teams t ON e.TeamID = t.Team_ID
JOIN Fest f ON t.Fest_ID = f.Fest_ID;


