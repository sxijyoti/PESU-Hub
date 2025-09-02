-- TASK 1
CREATE DATABASE University_Fest;
USE University_Fest;

CREATE TABLE Fest (
    Fest_ID INT PRIMARY KEY,
    Fest_name VARCHAR(100) NOT NULL,
    Year INT NOT NULL,
    Head_teamID INT
);

CREATE TABLE Teams (
    Team_ID INT PRIMARY KEY,
    Team_name VARCHAR(100) NOT NULL,
    Team_type ENUM('MNG', 'ORG') DEFAULT 'ORG',
    Fest_ID INT NOT NULL,
    FOREIGN KEY (Fest_ID) REFERENCES Fest(Fest_ID)
);

ALTER TABLE Fest 
    ADD CONSTRAINT fk_head_team FOREIGN KEY (Head_teamID) REFERENCES Teams(Team_ID);

CREATE TABLE Members (
    Mem_ID INT PRIMARY KEY,
    Mem_name VARCHAR(100) NOT NULL,
    DOB DATE NOT NULL,
    super_MemID INT,
    TeamID INT NOT NULL,
    FOREIGN KEY (super_MemID) REFERENCES Members(Mem_ID),
    FOREIGN KEY (TeamID) REFERENCES Teams(Team_ID)
);

CREATE TABLE Event (
    Event_ID INT PRIMARY KEY,
    Event_name VARCHAR(100) NOT NULL,
    Building VARCHAR(50) NOT NULL,
    Floor VARCHAR(20) NOT NULL,
    Room_no VARCHAR(20) NOT NULL,
    Price DECIMAL(8,2) CHECK(Price <= 1500),
    TeamID INT NOT NULL,
    FOREIGN KEY (TeamID) REFERENCES Teams(Team_ID) ON DELETE CASCADE
);

CREATE TABLE Event_conduction (
    Event_ID INT,
    Date_of_conduction DATE NOT NULL,
    PRIMARY KEY (Event_ID, Date_of_conduction),
    FOREIGN KEY (Event_ID) REFERENCES Event(Event_ID) ON DELETE CASCADE
);

CREATE TABLE Participants (
    SRN VARCHAR(20) PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Department VARCHAR(50),
    Semester INT CHECK(Semester BETWEEN 1 AND 8),
    Gender CHAR(1) 
);

CREATE TABLE Visitors (
    SRN VARCHAR(20),
    Name VARCHAR(100) NOT NULL,
    Age INT CHECK(Age > 0),
    Gender CHAR(1),
    PRIMARY KEY (SRN, Name),
    FOREIGN KEY (SRN) REFERENCES Participants(SRN) ON DELETE CASCADE
);

CREATE TABLE Registration (
    RegistrationID INT,
    Event_ID INT,
    SRN VARCHAR(20),
    PRIMARY KEY (RegistrationID, Event_ID, SRN),
    FOREIGN KEY (Event_ID) REFERENCES Event(Event_ID) ON DELETE CASCADE,
    FOREIGN KEY (SRN) REFERENCES Participants(SRN)
);

CREATE TABLE Stall (
    Stall_ID INT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Fest_ID INT NOT NULL,
    FOREIGN KEY (Fest_ID) REFERENCES Fest(Fest_ID)
);

CREATE TABLE Item (
    Item_name VARCHAR(100) PRIMARY KEY,
    Type ENUM('Veg','Non-veg') NOT NULL
);

CREATE TABLE Stall_items (
    Stall_ID INT,
    Item_name VARCHAR(100),
    Price_per_unit DECIMAL(8,2) NOT NULL DEFAULT 50,
    Total_quantity INT CHECK(Total_quantity <= 150),
    PRIMARY KEY (Stall_ID, Item_name),
    FOREIGN KEY (Stall_ID) REFERENCES Stall(Stall_ID),
    FOREIGN KEY (Item_name) REFERENCES Item(Item_name)
);

CREATE TABLE Purchased (
    SRN VARCHAR(20),
    Stall_ID INT,
    Item_name VARCHAR(100),
    Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    Quantity INT CHECK(Quantity > 0),
    PRIMARY KEY (SRN, Stall_ID, Item_name, Timestamp),
    FOREIGN KEY (SRN) REFERENCES Participants(SRN) ON DELETE CASCADE,
    FOREIGN KEY (Stall_ID, Item_name) REFERENCES Stall_items(Stall_ID, Item_name) ON DELETE CASCADE
);

DESC Fest;
DESC Teams;
DESC Members;
DESC Event;
DESC Event_conduction;
DESC Participants;
DESC Visitors;
DESC Registration;
DESC Stall;
DESC Item;
DESC Stall_items;
DESC Purchased;

-- TASK 2
-- Q1
DESC Participants;
ALTER TABLE Participants 	MODIFY Gender ENUM('M','F','O') AFTER Name;
DESC Participants;

-- Q2
DESC Stall_items;
ALTER TABLE Stall_items     MODIFY Price_per_unit DECIMAL(8,2) NOT NULL DEFAULT 50;
DESC Stall_items;

-- Q3
DESC Stall_items;
ALTER TABLE Stall_items     ADD CONSTRAINT chk_max_stock CHECK (Total_quantity <= 150);
DESC Stall_items;

-- Q4
SHOW TABLES;
RENAME TABLE Event_conduction TO Event_schedule;
SHOW TABLES;

-- Q5
DESC Event_schedule;
ALTER TABLE Event_schedule     MODIFY Date_of_conduction DATE FIRST;
DESC Event_schedule;
