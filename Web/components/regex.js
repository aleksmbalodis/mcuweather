
//validates Date by using regex
export function validateDate(input) {
    let regex = /[0-9]{4}-[0-9]{2}-[0-9]{2}T(0?[0-9]|1[0-9]|2[0-3]):[0-9]+/i;
    return regex.test(input);
}