


export default function Filter({ filter, setFrom, setTo }) {


    return (
        <form onSubmit={filter}>
                <label htmlFor="date-from">from:</label>
                <input name="date-from" type="datetime-local" onChange={(e) => {
                        setFrom(e.target.value)
                        // console.log(from)
                        // data = fetchData(filter)
                }}></input>
                <label htmlFor="date-to">to:</label>
                <input name="date-to" type="datetime-local" onChange={(e) => {
                        setTo(e.target.value)
                        // console.log(to)
                        // data = fetchData(filter)
                }}></input>
                <input type='submit'></input>
            </form>
    )
}