// import useSWR from "swr";

// const fetcher = (...args) => fetch(...args).then(res => res.json())


// export async function getData(from, to)
// {
//     var result

//     if(from && to) {
//         result = useSWR(`api/data/${from}/${to}`,fetcher)
//         return result.data
//     }
//     else {
//         result = useSWR(`api/data`,fetcher)
//         return result
//     }
// }