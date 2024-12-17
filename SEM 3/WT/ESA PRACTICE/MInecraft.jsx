import React, { useRef } from 'react';

function MinecraftTools() {
    const sticksRef = useRef(1);
    const stonesRef = useRef(1);
    const resultRef = useRef(null);

    const computeAxes = () => {
        const sticks = Math.floor(sticksRef.current.value / 2);
        const stones = Math.floor(stonesRef.current.value / 3);
        const axes = Math.min(sticks, stones);
        resultRef.current.textContent = `Number of axes: ${axes}`;
    };

    return (
        <div>
            <label>
                Sticks: <input type="number" defaultValue="1" ref={sticksRef} />
            </label>
            <br />
            <label>
                Stones: <input type="number" defaultValue="1" ref={stonesRef} />
            </label>
            <br />
            <button onClick={computeAxes}>Compute</button>
            <div ref={resultRef}>Number of axes: 0</div>
        </div>
    );
}

export default MinecraftTools;
