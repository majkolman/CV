1 + (let x = 1 + 3 in x * x) + 1;;                      

let vsota_lihih_42 =
  let v = ref 0 in
  let i = ref 0 in
  while !i < 42 do
    v := !v + (2 * !i + 1) ;
    i := !i + 1
  done ;
  !v;;

let vsota1 n =
  let i = ref 0 in
  let s = ref 0 in
  while !i <= n do
    s := !s + !i;
    i := !i + 1
  done ;
  !s;;

let fib n =
  let p = ref (-1) in
  let c = ref 1 in
  let i = ref 0 in
  while !i <= n do
    let temp = !c in
    c := temp + !p ;
    p := temp ;
    i := !i + 1
  done ;
  !c;;

let rec vsota2 n =
  if n > 0 then
    n + vsota2 (n-1)
  else
    0;;
  
let rec fib2 n =
  if n >= 2 then
    fib2 (n-1) + fib2 (n-2)
  else if n == 1 then
    1
  else
    0;;

let vsota3 n =
  let rec vsota i s =
    if i <= n then
      vsota (i + 1) (s + i)
    else
      s
  in
  vsota 0 0;;

let fib3 n =
  let rec fib p c i =
    if i <= n then
      fib (c) (p+c) (i+1)
    else 
      c
    in
  fib (2) (-1) (-1);;


let zanka s0 p f r =
  let rec loop s =
    if p s then loop (f s) else r s
  in
  loop s0;;

let vsota4 n = zanka (0,0) (fun (i,s) ->(i<=n)) (fun (i,s) ->(i+1,i+s)) (fun(i,s)->s);;

let fib4 n = zanka ((-1),1,0) (fun (p,c,i) -> (i<=n)) (fun (p,c,i) -> (c,p+c,i+1)) (fun (p,c,i) -> c);;

let forzanka s0 a b f r =
  let rec loop s =
    if a <= b then loop (f s) else r s
  in
  loop s0;;