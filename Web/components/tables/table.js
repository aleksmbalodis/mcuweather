export default function Table({ children , styles, content}) {
    console.log(content, "table")

    return (
        <table className={styles.table}>
            {children}
        </table>

    )
}