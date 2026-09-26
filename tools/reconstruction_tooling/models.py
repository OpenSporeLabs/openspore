import hashlib
import json
import os
import re
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HEX = re.compile(r"^(?:0x)?([0-9a-fA-F]{1,8})$")


class ToolError(Exception):
    def __init__(self, code, message, exit_code=1, details=None):
        super().__init__(message)
        self.code = code
        self.message = message
        self.exit_code = exit_code
        self.details = details or {}


def normalize_va(value):
    if isinstance(value, bool):
        raise ValueError("boolean is not a VA")
    if isinstance(value, int):
        number = value
    else:
        text = str(value).strip().lower()
        if text.startswith("rva:"):
            text = text[4:]
        match = HEX.match(text)
        if not match:
            raise ValueError("invalid VA: %r" % value)
        number = int(match.group(1), 16)
    if number < 0 or number > 0xFFFFFFFF:
        raise ValueError("VA outside x86-32 range: %r" % value)
    return "0x%08x" % number


def canonical_json(value):
    return json.dumps(value, indent=2, sort_keys=True, ensure_ascii=False) + "\n"


def load_json(path):
    with Path(path).open(encoding="utf-8") as handle:
        return json.load(handle)


def optional_json(path):
    try:
        return load_json(path)
    except (OSError, ValueError):
        return None


def write_json_atomic(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    payload = canonical_json(value)
    descriptor, temporary = tempfile.mkstemp(prefix=path.name + ".", dir=str(path.parent))
    try:
        with os.fdopen(descriptor, "w", encoding="utf-8") as handle:
            handle.write(payload)
            handle.flush()
            os.fsync(handle.fileno())
        os.replace(temporary, path)
        os.chmod(path, 0o644)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)
    return path


def write_text_atomic(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor, temporary = tempfile.mkstemp(prefix=path.name + ".", dir=str(path.parent))
    try:
        with os.fdopen(descriptor, "w", encoding="utf-8") as handle:
            handle.write(value)
            handle.flush()
            os.fsync(handle.fileno())
        os.replace(temporary, path)
        os.chmod(path, 0o644)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)
    return path


def sha256_bytes(value):
    if isinstance(value, str):
        value = value.encode("utf-8")
    return hashlib.sha256(value).hexdigest()


def sha256_json(value):
    return sha256_bytes(canonical_json(value))


def file_sha256(path):
    digest = hashlib.sha256()
    with Path(path).open("rb") as handle:
        for block in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def relative(path, root=ROOT):
    try:
        return str(Path(path).resolve().relative_to(Path(root).resolve())).replace(os.sep, "/")
    except (OSError, ValueError):
        return str(path).replace(os.sep, "/")


def bounded(value, limit=1200):
    if isinstance(value, str):
        return value if len(value) <= limit else value[:limit] + "…"
    if isinstance(value, list):
        return [bounded(item, limit) for item in value]
    if isinstance(value, dict):
        return {str(key): bounded(item, limit) for key, item in sorted(value.items())}
    return value


def compact(value, max_bytes=12000):
    payload = canonical_json(value)
    if len(payload.encode("utf-8")) <= max_bytes:
        return value
    encoded = payload.encode("utf-8")
    return {
        "truncated": True,
        "original_bytes": len(encoded),
        "sha256": sha256_bytes(payload),
        "preview": encoded[:max_bytes].decode("utf-8", errors="ignore"),
    }
