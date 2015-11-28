# KeyFinder
C algorithm to generate keys for a relation based on its functional dependencies

This algorithm reads from a text file (default is dfs.txt) the attributes and the functional dependencies of a relation and generates all possible non-trivial keys for it.

An attribute need to be a single character (at least for now).

An example of how to write the text file for this relation R:
```
R(A, B, C, D, E, G)
With FD's:
AB->C	BE->C
D->EG	BC->D
C->A	CG->BD
ACD->B	CE->AG
```
Should be (.txt):
```
ABCDEG   //all together
8         //-> number of functional dependencies to follow
AB -> C   //Each FD separated by a line wrap, separating the left side from the right side with space, '->' and space.
D -> EG
C -> A
ACD -> B
BE -> C
BC -> D
CG -> BD
CE -> AG
```

Output(chaveFinder.exe):
```
ab -> c
d -> eg
c -> a
acd -> b
be -> c
bc -> d
cg -> bd
ce -> ag
abcdeg
key: ab
key: acd
key: ace
key: bc
key: cg
```
