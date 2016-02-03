# Atkin
Atkin sieve for prime number generation.

## Build

Run `make`. 

## Usage

```bash
primegen [-mn]

 -m <min>	Start at min value
 -n <max>	Stop when max is reached
 -h		This help
```

`./primegen -m 10 -n 200000` generates all primenumbers between 10 and 200000. By default the min is set to 2 and max to 1000000000.
