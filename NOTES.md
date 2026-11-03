# Notes
Notes about the algorithm as I design and implement it go here.

## Algorithm description
We basically want to look at the front face, and when it changes, look for moves that
might have brought it from one of its prior candidate states to a new candidate state.

Important to note:
- We always know the start and end state of the cube
- The final observable "state change" (that is, the last time we detect the F-face changing) will have the cube either solved or some hidden moves away from solved

As we step through options to transition from prior candidate states to a new state that includes the current F-face, we will be able to 
eliminate some of these prior candidate states for which a transition is not possible. Realistically, the number of candidate states should always be fairly small.
Eventually, there will hopefully only be one candidate state with a valid transition to a solved state or to a state that is some hidden moves away from solved (idk).

Every candidate state should be represented by its actual cube state (to save on having to re-compute visited states) but also by the sequence of moves that has brought the cube to this state (to instantly identify the solution).
## Hidden moves
Between two observed states, there may have been at least one hidden move to consider
as a prefix to candidate moves (and so there may be more than one move that takes a cube from ```S_{n-1}``` to ```S_n```).
We must consider the following prefixes:
- B-layer moves: always
- F2: when half-symmetric ```S_{n-1}``` front face
- F, F', F2: when fully-symmetric ```S_{n-1}``` front face
- U-layer moves: when the row that moves to the front face is the same as stickers 0, 1, 2 (top row) of the ```S_{n-1}``` front face.
- R-layer moves: extends from the U-layer logic
- L-layer moves: extends from the U-layer logic
- D-layer moves: extends from the U-layer logic

Once we test for one hidden prefix move, we also need to test the resulting possible cube states after this single move is applied for any subsequent possible
hidden moves (i.e. <B\> might be a valid prefix on its own, but so might <B, U>). We build up possible prefixes by:
- Pick a valid hidden move that has not already been chosen and add it to the list of possible prefixes (1)
- For each of the possible states we have for ```S_{n-1}```: (2)
  - Add the current prefix
  - Use the new state to determine whether there are any possible hidden moves at this
    state. If there are moves, for each of them do:
    - Add the move to the current prefix
    - Repeat (2)
  - If we have exhausted possible further hidden moves, add the current prefix to the list of
    possible prefixes and go to (1)
- If all hidden moves have now been exhausted, we have constructed every possible prefix.

Once we have a list of possible prefixes, we can test for non-hidden moves that bring us from a prefix state
to ```S_n```. We may as well add an empty prefix to the list of possible prefixes for a clean implementation (the solution can be such that it always searches from each of the possible prefixes).

This whole thing is some recursive bullshit and it's so fucking ugly im going to go insane trying to implement this