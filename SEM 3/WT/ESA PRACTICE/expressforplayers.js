// players.js
const express = require('express');
const router = express.Router();

router.get('/', (req, res) => res.send('All players'));
router.post('/', (req, res) => res.send('Add a player'));
router.get('/:id', (req, res) => res.send(`Player ${req.params.id}`));
module.exports = router;

// server.js
const express = require('express');
const app = express();

app.use('/players', require('./routes/players'));
app.use('/matches', require('./routes/matches'));
app.use('/teams', require('./routes/teams'));

app.listen(3000, () => console.log('Server is running on port 3000'));
