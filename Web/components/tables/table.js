export default function Table({ children , styles, content}) {
    console.log(content, "table")

    return (
        <table className={styles.table}>
            {children}
            {content.map(({_id, date, temperature, humidity, brightness}) => (
                <tr key={_id} className={styles.tableRow}>
                    <td>{new Date(date).toUTCString("dd/mm/yy")}</td>
                    {/* <td>{new Date(date).toTimeString()}</td> */}
                    <td>{temperature}</td>
                    <td>{humidity}</td>
                    <td>{brightness}</td>
                </tr>
            ))}
        </table>

    )
}