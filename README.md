# testTree-Program
Comparison of AVL with BST and LazyAVL with NonLazy AVL

BST
Number of calls to insert=10686
Number of total nodes= 565
Average depth= 10.3274
Ratio of average depth to log2n =1.129
Number of calls to the contains function= 5253
After removing every other sequence
Number of calls to the delete function =2647
Average depth= 10.328
Ratio of average depth to log2n =1.13
Number of calls to the contains function= 5253

AVL
Number of calls to insert=8368
Number of total nodes= 565
Average depth= 7.375
Ratio of average depth to log2n =.8067
Number of calls to the contains function= 4307
After removing every other sequence
Number of calls to the delete function =2141
Average depth= 7.374
Ratio of average depth to log2n = .8068
Number of calls to the contains function= 4307

LazyAVL
Number of calls to insert=8368
Number of total nodes= 565
Average depth= 7.375
Ratio of average depth to log2n =.8067
Number of calls to the contains function= 4307
After removing every other sequence
Number of calls to the delete function =2141
Average depth= 7.374
Ratio of average depth to log2n = .8068
Number of calls to the contains function= 4307

In the comparison of AVL vs BST, the results are not really surprising. On average, AVL trees
have a better performance than BST. Since it has less calls than BST, it also is faster than the
BST. Also the fact that AVL tree can rebalance itself makes it faster with less calls. Also since
AVL trees tend to be more balanced than BST trees I expected the average depth to be low.

In the comparison of LazyAVL vs NonLazy, I expected the NonLazy AVL to have less calls to all
the functions compared to NonLazy but I wasn’t too surprised with the results. In a LazyAVL, it
would be expected that there would be less call to deletion since the items are only marked for
deletion and there is no shifting of the data structures. Also there should be less calls to
insertion since it can write over the first delete.However, with Lazy Deletion you have to traverse
twice to delete an item and once again to delete it
