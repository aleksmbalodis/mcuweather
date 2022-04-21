
import styles from "../styles/Loading.module.css"

export default function Loading({}) {


    return (
        <div className={styles.loading}>
            <h1>Loading...</h1>
            <div className={styles.animation}>
                <div className={styles.center}></div>
            </div>
        </div>
    )
}