# Bitcoin Paper Double Spend Attack Computation

TLDR: How many bitcoin blocks confirmations should a receiver of a payment wait for before the odds of a double spend attack drop below a tolerance level such as 1%. To compute this, enter the probability with which we think an attacker can mine a block.


The primary purpose of proof of work is to implement bitcoin as a peer to peer distributed timestamp server. This makes the system decentralized (not just distributed) and provides protection against the main security problem - a double spending attack. In order to carry it out, the attacker must be able to mine a different block in which they include the double-spending transaction. If the attacker's hashrate is more than the network's, then the attack becomes trivial. In order for Nakamoto consensus to work as intended, we must have a honest majority of mining power. 


Suppose the probability with which the attacker finds the next block is given by `q`. From our honest majority assumption, this probability must be less than half. The probability that a honest miner finds the next block is `p = 1-q`. In section 11 of the bitcoin paper, Satoshi derives the analytical probability of a double spend attack succeeding: The expression for this probability is a function of `q`, and the number of blocks `z` since the original payment was mined. Satoshi also provides the C code to compute this probability - which is used here.


## How to use
I started with a boilerplate gradle starter app and added Satoshi's C code from the paper.

`gradle build` or `./gradlew build` to create the executable. Run the executable with `./app/build/exe/main/debug/app`

And then enter a value for the probability with which the attacker finds the next block. This must be a value between 0 and 0.5. 

For example, if the attacker has enough hashrate such that they will find the next block with probability 10% (i.e `q=0.1`), then after 5 blocks, the attackers success rate of including the double spend drops to 0.34%



```
Input probability is: 0.1

z        P
------------ 
1       1
2       0.204587
3       0.0509779
4       0.0131722
5       0.00345524

```

Suppose we have a powerful adversary, an attacker with access to hashpower similar to a major mining pool), with `q` is 0.33 (i.e. 33%). Then a recipient of a payment has to wait 21 block confirmations before the attacker's success rate drops below 1%. After 32 blocks, even a powerful attacker's ability to doulbe spend drops to less than 0.1%.

```
Input probability is: 0.33

z        P
------------ 
1       1
2       0.689903
3       0.530512
4       0.417303
5       0.331739
6       0.265357
7       0.213127
8       0.171674
9       0.138583
10      0.112057
11      0.0907297
12      0.0735411
13      0.0596624
14      0.0484395
15      0.039353
16      0.0319888
17      0.0260151
18      0.021166
19      0.0172271
20      0.0140259
21      0.011423
22      0.0093055
23      0.00758246
24      0.00617978
25      0.00503758
26      0.00410724
27      0.00334927
28      0.0027316
29      0.00222815
30      0.00181773
31      0.00148309
32      0.00121019
33      0.000987613
```


