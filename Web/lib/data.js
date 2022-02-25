import useSWR from "swr"
import { getPostData } from "../../Beta/web/lib/posts"

const fetcher = url => fetch(url).then(r => r.json())



export default function getData(filter)
{

    // console.log(filter)
    if(!filter)
    const url = filter ? `/api/data/${filter.from}/${filter.to}` : `/api/data`
    const res = useSWR(url, fetcher)
    // console.log(data)
    return res
}

export getSortedData(date) {

}