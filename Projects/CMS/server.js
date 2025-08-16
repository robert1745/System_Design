require("dotenv").config();
const express = require("express");
const { Pool } = require("pg");

const app = express();
app.use(express.json());


// --- DB Connection ---
const pool = new Pool({
  user: process.env.DB_USER,
  host: process.env.DB_HOST || "localhost",
  database: process.env.DB_NAME,
  password: process.env.DB_PASSWORD,
  port: process.env.DB_PORT || 5432,
});



// --- Routes ---
// Create Citizen
app.post("/citizens", async (req, res) => {
  const { fname, lname, age, gender } = req.body;
  if (!fname || !lname || !age || !gender) {
    return res.status(400).json({ error: "All fields are required" });
  }

  try {
    const result = await pool.query(
      "INSERT INTO citizens (fname, lname, age, gender) VALUES ($1, $2, $3, $4) RETURNING *",
      [fname, lname, age, gender]
    );
    res.status(201).json(result.rows[0]);
  } catch (err) {
    console.error("Insert error:", err);
    res.status(500).json({ error: "Failed to create citizen" });
  }
});

// Get Citizens (with optional vote filter)
app.get("/citizens", async (req, res) => {
  const { vote } = req.query;
  try {
    const query =
      vote === "true"
        ? "SELECT * FROM citizens WHERE (permissions->>'vote')::boolean = true ORDER BY id"
        : "SELECT * FROM citizens ORDER BY id";

    const result = await pool.query(query);
    res.json(result.rows);
  } catch (err) {
    console.error("Fetch error:", err);
    res.status(500).json({ error: "Failed to fetch citizens" });
  }
});

// Update Citizen (age + permissions in transaction)
app.put("/citizens/:id/age", async (req, res) => {
  const client = await pool.connect();
  try {
    await client.query("BEGIN");

    const { id } = req.params;
    const { newAge } = req.body;
    if (!newAge) {
      return res.status(400).json({ error: "newAge is required" });
    }

    // Update age
    await client.query("UPDATE citizens SET age = $1 WHERE id = $2", [
      newAge,
      id,
    ]);

    // Update permissions
    await client.query(
      `UPDATE citizens
       SET permissions = jsonb_set(permissions, '{vote}',
         CASE WHEN age >= 18 THEN 'true'::jsonb ELSE 'false'::jsonb END, true)
       WHERE id = $1`,
      [id]
    );

    await client.query("COMMIT");
    res.json({ message: "Age updated successfully", newAge });
  } catch (err) {
    await client.query("ROLLBACK");
    console.error("Transaction error:", err);
    res.status(500).json({ error: "Failed to update citizen" });
  } finally {
    client.release();
  }
});

// Delete Citizen
app.delete("/citizens/:id", async (req, res) => {
  try {
    const result = await pool.query(
      "DELETE FROM citizens WHERE id = $1 RETURNING *",
      [req.params.id]
    );
    if (result.rows.length === 0) {
      return res.status(404).json({ error: "Citizen not found" });
    }
    res.json({ message: "Citizen deleted", citizen: result.rows[0] });
  } catch (err) {
    console.error("Delete error:", err);
    res.status(500).json({ error: "Failed to delete citizen" });
  }
});

// --- Server ---
const PORT = process.env.PORT || 3000;
app.listen(PORT, () =>
  console.log(`🚀 Server running at http://localhost:${PORT}`)
);
