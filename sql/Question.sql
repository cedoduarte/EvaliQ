CREATE TABLE Question (
    QuestionID INT IDENTITY(1,1) PRIMARY KEY,   -- Unique identifier for each question, auto-incrementing
    QuestionText NVARCHAR(MAX) NOT NULL,        -- The text of the question with unlimited length that can hold up to 2 GB of text
    Category NVARCHAR(100),                     -- Category or topic of the question (optional)
    Ponderation DECIMAL(5,2) NOT NULL,          -- Weight or ponderation for the question
	AnswerText NVARCHAR(MAX) NOT NULL,
    CreatedAt DATETIME DEFAULT GETDATE(),       -- Timestamp for when the question was created
    UpdatedAt DATETIME DEFAULT GETDATE()        -- Timestamp for when the question was last updated
);
