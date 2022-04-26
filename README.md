This repo is one of the projects in the [15-780](https://www.cs.cmu.edu/~./15780/#project) course (Graduate Artificial Intelligence, Spring'22) of CMU.

It reproduces a part of Figure 2 of the paper [Can We Predict the Election Outcome from Sampled Votes?](https://ojs.aaai.org/index.php/AAAI/article/view/5593) in AAAI-20.

It also computes the top-k average-case predictability. (Can we predict the top-k election outcome instead of the full outcome?) In some cases, for example, we only care about the top-1 election outcome.

### To run

Simply compile the single file `voting_top_k.cpp` and run to get the result. It takes about 30 seconds.

To plot the result, copy the output of `voting_top_k.cpp` to the corresponding part of `plot.py`, and run `plot.py`.

### Extension

`voting_top_k.cpp` can be easily extended for other voting rules and other parameters (e.g., changing the parameters n=1000, m=5, #draws=10^6, or the plotting number of samples in the paper).