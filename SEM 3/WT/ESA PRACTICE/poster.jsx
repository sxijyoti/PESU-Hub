import React from 'react';

function Poster({ src, title, director }) {
    return (
        <div>
            <img src={src} alt={title} width="200" />
            <p><strong>Title:</strong> {title}</p>
            <p><strong>Director:</strong> {director}</p>
        </div>
    );
}

function App() {
    const movies = [
        { src: 'poster1.jpg', title: 'Inception', director: 'Christopher Nolan' },
        { src: 'poster2.jpg', title: 'Interstellar', director: 'Christopher Nolan' },
        { src: 'poster3.jpg', title: 'Dunkirk', director: 'Christopher Nolan' },
    ];

    return (
        <div>
            {movies.map((movie, index) => (
                <Poster key={index} {...movie} />
            ))}
        </div>
    );
}

export default App;
